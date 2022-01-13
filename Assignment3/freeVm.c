void
freevm(pde_t *pgdir)
{
   uint i, j, k;

   if(pgdir == 0)
     panic("freevm: no pgdir");
   deallocuvm(pgdir, USERTOP, 0);
   for(i = 0; i < NPDENTRIES; i++){
     if(pgdir[i] & PTE_P) {
       for (j = 0; j < NUM_KEYS; j++) {
         if (is_key_used[i] != 0) {  // Shared page is being used. Not to be
                                       // freed for sure.
           break;
         }
         for(k = 0; k < NUM_PAGES; k++) {
           if((char*)P2V(PTE_ADDR(pgdir[i])) == key_page_addrs[i][k]) {
             break;
           }
         }
       }
       // Dont free the shared pages that are being used used
       if (j == NUM_KEYS && k == NUM_PAGES)
         kfree((char*)P2V(PTE_ADDR(pgdir[i])));
     }
   }
   kfree((char*)pgdir);
   }



void
freevm(pde_t *pgdir)
{
  uint i;

  if(pgdir == 0)
    panic("freevm: no pgdir");
  deallocuvm(pgdir, KERNBASE, 0);
  for(i = 0; i < NPDENTRIES; i++){
    if(pgdir[i] & PTE_P){
      char * v = P2V(PTE_ADDR(pgdir[i]));
      kfree(v);
    }
  }
  kfree((char*)pgdir);
}




void
freevm(pde_t *pgdir)
{
  uint i;

  if(pgdir == 0)
    panic("freevm: no pgdir");
  deallocuvm(pgdir, KERNBASE, 0);
  for (j = 0; j < NUM_KEYS; j++) {
	if (is_key_used[j] != 0) {  // Shared page is being used. Not to be
		break;
	}
	for(k = 0; k < NUM_PAGES; k++) {
	   if(!(char*)P2V(PTE_ADDR(pgdir[i])) == key_page_addrs[j][k]) {
		 if(pgdir[i] & PTE_P){
			char * v = P2V(PTE_ADDR(pgdir[i]));
			kfree(v);
		  }
	   }
    }
  }
  kfree((char*)pgdir);
}


for (j = 0; j < NUM_KEYS; j++) {
	if (is_key_used[j] != 0) {  // Shared page is being used. Not to be
		break;
	}
	for(k = 0; k < NUM_PAGES; k++) {
	   if(!(char*)PTE_ADDR(pgdir[i]) == key_page_addrs[j][k]) {
		 if(pgdir[i] & PTE_P){
      char * v = P2V(PTE_ADDR(pgdir[i]));
      kfree(v);
		  }
	   }
    }
	

}


for (i = 0; i < NUM_KEYS; i++) {
    curproc->keys[i] = np->keys[i];
    for(j = 0; j < NUM_PAGES; j++) {
      curproc->page_addrs[i][j] = np->page_addrs[i][j];
    }
  }
curproc->top = np->top;
