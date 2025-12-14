/**
 * \file ListeChaineeFile.h
 * \brief Implémentation d'une file utilisant une liste chaînée.
 * \author Nicolas Delestre et IA générative
 * \version 1.0
 * \date 2025
 **/

#ifndef __LISTECHAINEEFILE_H__
#define __LISTECHAINEEFILE_H__

#include <stdbool.h>
#include "listeChainee.h"
#include "copieLiberationComparaison.h"

/**
 * \struct LCF_ListeChaineeFile
 * \brief Représentation d'une file (FIFO) avec liste chaînée.
 */
typedef struct LCF_ListeChaineeFile {
  LC_ListeChainee teteFile;   /**< Pointeur vers le premier élément de la file */
  LC_ListeChainee queueFile;  /**< Pointeur vers le dernier élément de la file */
  CLC_FonctionCopier copierElement;     /**< Fonction de copie des éléments */
  CLC_FonctionLiberer supprimerElement; /**< Fonction de libération des éléments */
} LCF_ListeChaineeFile;

#define FILE_VIDE_ERREUR 1

/**
 * \brief Crée une file vide.
 * \param copierElement Fonction de copie des éléments.
 * \param supprimerElement Fonction de libération des éléments.
 * \return Une file vide initialisée.
 */
LCF_ListeChaineeFile LCF_file(CLC_FonctionCopier copierElement,
                              CLC_FonctionLiberer supprimerElement);

/**
 * \brief Vérifie si la file est vide.
 * \param file La file à vérifier.
 * \return true si la file est vide, false sinon.
 */
bool LCF_estVide(LCF_ListeChaineeFile file);

/**
 * \brief Enfile un élément à la fin de la file.
 * \param pfile Pointeur vers la file.
 * \param element L'élément à enfiler.
 */
void LCF_enfiler(LCF_ListeChaineeFile* pfile, void* element);

/**
 * \brief Défile un élément du début de la file.
 * \param pfile Pointeur vers la file.
 * \return L'élément défilé, ou NULL et ERRNO est mis à FILE_VIDE_ERREUR si la file est vide.
 */
void* LCF_defiler(LCF_ListeChaineeFile* pfile);

/**
 * \brief Accède à l'élément en tête de file sans le défiler.
 * \param file La file.
 * \return L'élément en tête de file, ou NULL si la file est vide.
 */
void* LCF_element(LCF_ListeChaineeFile file);

/**
 * \brief Vide la file et libère la mémoire associée.
 * \param pfile Pointeur vers la file à vider.
 */
void LCF_vider(LCF_ListeChaineeFile* pfile);

#endif
