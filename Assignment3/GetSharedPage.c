void*
getSharedPage(int key, int num_pages)
{
  int i;
  // Check for valid params
  if (key < 0 || key > 7) {
    return (void*)-1;
  }
  if (num_pages < 1 || num_pages > 4) {
    return (void*)-1;
  }

  // If this is the first time that proc is calling shmgetat, set top to USERTOP
  for(i = 0; i < NUM_KEYS; i++) {
    if(proc->keys[i] == 1) {
      break;
    }
  }
  if(i == NUM_KEYS) {
    proc->top = USERTOP;
  }

  // Update ref count if process isnt already using this key
  if (proc->keys[key] == 0) {
    key_ref_count[key]++;
    proc->keys[key] = 1;
  }

  // Allocate memory if key hasnt been used yet
  if (is_key_used[key] == 0) {
    // Check if trying to access already allocated memory
    if ((proc->top - num_pages*PGSIZE) < proc->sz) {
      return (void*)-1;
    }
    // Allocate physical memory and make the va-pa mappings
    char* mem;
    for(i = 0; i < num_pages; i++) {
      mem = kalloc();  // Physical memory
      if (mem == 0) {
        cprintf("allocuvm out of memory\n");
        return (void*)-1;
      }
      memset(mem, 0, PGSIZE);

      // Store the physical page for future use
      key_page_addrs[key][i] = mem;

      // Set up mapping for this process
      // VA.
      void* addr = (void*)(proc->top - PGSIZE);
      proc->page_addrs[key][i] = addr;

      // Change address of next available VP
      proc->top -= PGSIZE;

      // Map vp to pp
      if (mappages(proc->pgdir, addr, PGSIZE, PADDR(mem), PTE_P|PTE_W|PTE_U) < 0) {
        return (void*)-1;
      }
    }
    is_key_used[key] = 1;
    num_key_pages[key] = num_pages;
  } else { // Key is being used
    if (proc->keys[key] == 0) { // Check if this process is currently using key
      // Create mapping for va-pa for this new process
      for(i = 0; i < NUM_PAGES; i++) {
        // VA.
        void* addr = (void*)(proc->top - PGSIZE);
        proc->page_addrs[key][i] = addr;

        // Change address of next available VP
        proc->top -= PGSIZE;

        // Map vp to pp
        if (mappages(proc->pgdir, addr, PGSIZE,
             PADDR(key_page_addrs[key][i]), PTE_P|PTE_W|PTE_U) < 0) {
          return (void*)-1;
        }
      }
    }
  }
  return proc->page_addrs[key][num_key_pages[key]-1];
}