#include <stdlib.h>
#include <errno.h>
#include "ListeChaineeFile.h"

LCF_ListeChaineeFile LCF_file(CLC_FonctionCopier copierElement,
                              CLC_FonctionLiberer supprimerElement) {
  LCF_ListeChaineeFile file;

  file.teteFile = LC_listeChainee();
  file.queueFile = file.teteFile;
  file.copierElement = copierElement;
  file.supprimerElement = supprimerElement;
  return file;
}

bool LCF_estVide(LCF_ListeChaineeFile file) {
  return LC_estVide(file.teteFile) != 0;
}

void LCF_enfiler(LCF_ListeChaineeFile* pfile, void* element) {
  LC_ListeChainee nouvel;  

  if (LCF_estVide(*pfile)) {
    LC_ajouter(&(pfile->teteFile), element, pfile->copierElement);
    pfile->queueFile = pfile->teteFile;
  } else {
    nouvel = LC_listeChainee();
    LC_ajouter(&nouvel, element, pfile->copierElement);
    LC_fixerListeSuivante(&(pfile->queueFile), nouvel);
    pfile->queueFile = nouvel;
  }
}

void* LCF_defiler(LCF_ListeChaineeFile* pfile) {
  void* element;  
  if (LCF_estVide(*pfile)) {
    errno = FILE_VIDE_ERREUR;
    return NULL;
  }
  element = pfile->copierElement(LC_obtenirElement(pfile->teteFile));
  LC_supprimerTete(&(pfile->teteFile), pfile->supprimerElement);

  if (LC_estVide(pfile->teteFile)) {
    pfile->queueFile = pfile->teteFile;
  }
  return element;
}

void* LCF_element(LCF_ListeChaineeFile file) {
  if (LCF_estVide(file)) {
    errno = FILE_VIDE_ERREUR;
    return NULL;
  }
  errno = 0;
  return file.copierElement(LC_obtenirElement(file.teteFile));
}

void LCF_vider(LCF_ListeChaineeFile* pfile) {
  while (!LCF_estVide(*pfile)) {
    LCF_defiler(pfile);
  }
}
