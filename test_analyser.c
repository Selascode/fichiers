/**
 * \file test_analyse.c
 * \brief Exemple d'utilisation du parseur de terrain
 */
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include "analyseur_terrain.h"

/* Variable globale pour le terrain de test */
static T_Terrain terrain_test;

int init_suite_success(void) { 
    FILE* fichier = fopen("map.txt", "r");
    if (fichier == NULL) {
        return -1;
    }
    terrain_test = AT_analyseurTerrain(fichier);
    fclose(fichier);
    return 0; 
}
/* -------------------------------------------------------------------------- */
/*                       TESTS : PROPRIÉTÉS DU TERRAIN                        */
/* -------------------------------------------------------------------------- */

void test_taille_terrain(void) {
    CU_ASSERT_EQUAL(T_obtenirTaille(terrain_test), 5);
}

void test_position_depart(void) {
    CO_Coordonnee posDepart = T_obtenirPositionDepart(terrain_test);
    CO_Coordonnee attendu = CO_NumeroCaseVersCoordonnee(6, 5);
    
    CU_ASSERT_EQUAL(CO_abscisse(posDepart), CO_abscisse(attendu));
    CU_ASSERT_EQUAL(CO_ordonnee(posDepart), CO_ordonnee(attendu));
    CU_ASSERT_EQUAL(CO_abscisse(posDepart), 0);
    CU_ASSERT_EQUAL(CO_ordonnee(posDepart), 1);
}

void test_direction_depart(void) {
    DI_Direction dirDepart = T_obtenirDirectionDepart(terrain_test);
    CU_ASSERT_EQUAL(dirDepart, N); // 'S' dans map.txt
}

/* -------------------------------------------------------------------------- */
/*                          TESTS : OBJECTIFS                                 */
/* -------------------------------------------------------------------------- */

void test_nombre_objectifs(void) {
    unsigned int nbObjectifs = THE_cardinalite(terrain_test.positionsObjectifs);
    CU_ASSERT_EQUAL(nbObjectifs, 3);
}

void test_objectif_case_13(void) {
    CO_Coordonnee coord13 = CO_NumeroCaseVersCoordonnee(13, 5);
    CU_ASSERT_TRUE(T_estUnObjectif(terrain_test, coord13));
}

void test_objectif_case_22(void) {
    CO_Coordonnee coord22 = CO_NumeroCaseVersCoordonnee(22, 5);
    CU_ASSERT_TRUE(T_estUnObjectif(terrain_test, coord22));
}

void test_objectif_case_20(void) {
    CO_Coordonnee coord20 = CO_NumeroCaseVersCoordonnee(20, 5);
    CU_ASSERT_TRUE(T_estUnObjectif(terrain_test, coord20));
}

void test_non_objectif_case_1(void) {
    CO_Coordonnee coord1 = CO_NumeroCaseVersCoordonnee(1, 5);
    CU_ASSERT_FALSE(T_estUnObjectif(terrain_test, coord1));
}

void test_non_objectif_case_25(void) {
    CO_Coordonnee coord25 = CO_NumeroCaseVersCoordonnee(25, 5);
    CU_ASSERT_FALSE(T_estUnObjectif(terrain_test, coord25));
}

/* -------------------------------------------------------------------------- */
/*                     TESTS : CHEMINS HORIZONTAUX                            */
/* -------------------------------------------------------------------------- */

void test_chemin_1_2(void) {
    CO_Coordonnee c1 = CO_NumeroCaseVersCoordonnee(1, 5);
    CO_Coordonnee c2 = CO_NumeroCaseVersCoordonnee(2, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c1, c2));
}

void test_chemin_2_3(void) {
    CO_Coordonnee c2 = CO_NumeroCaseVersCoordonnee(2, 5);
    CO_Coordonnee c3 = CO_NumeroCaseVersCoordonnee(3, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c2, c3));
}

void test_chemin_3_4(void) {
    CO_Coordonnee c3 = CO_NumeroCaseVersCoordonnee(3, 5);
    CO_Coordonnee c4 = CO_NumeroCaseVersCoordonnee(4, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c3, c4));
}

void test_chemin_11_12(void) {
    CO_Coordonnee c11 = CO_NumeroCaseVersCoordonnee(11, 5);
    CO_Coordonnee c12 = CO_NumeroCaseVersCoordonnee(12, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c11, c12));
}

/* -------------------------------------------------------------------------- */
/*                       TESTS : CHEMINS VERTICAUX                            */
/* -------------------------------------------------------------------------- */

void test_chemin_1_6(void) {
    CO_Coordonnee c1 = CO_NumeroCaseVersCoordonnee(1, 5);
    CO_Coordonnee c6 = CO_NumeroCaseVersCoordonnee(6, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c1, c6));
}

void test_chemin_6_11(void) {
    CO_Coordonnee c6 = CO_NumeroCaseVersCoordonnee(6, 5);
    CO_Coordonnee c11 = CO_NumeroCaseVersCoordonnee(11, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c6, c11));
}

void test_chemin_11_16(void) {
    CO_Coordonnee c11 = CO_NumeroCaseVersCoordonnee(11, 5);
    CO_Coordonnee c16 = CO_NumeroCaseVersCoordonnee(16, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c11, c16));
}

void test_chemin_16_21(void) {
    CO_Coordonnee c16 = CO_NumeroCaseVersCoordonnee(16, 5);
    CO_Coordonnee c21 = CO_NumeroCaseVersCoordonnee(21, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c16, c21));
}

/* -------------------------------------------------------------------------- */
/*                      TESTS : CHEMINS NON EXISTANTS                         */
/* -------------------------------------------------------------------------- */

void test_pas_de_chemin_1_3(void) {
    CO_Coordonnee c1 = CO_NumeroCaseVersCoordonnee(1, 5);
    CO_Coordonnee c3 = CO_NumeroCaseVersCoordonnee(3, 5);
    CU_ASSERT_FALSE(T_cheminExiste(terrain_test, c1, c3));
}

void test_pas_de_chemin_1_7(void) {
    CO_Coordonnee c1 = CO_NumeroCaseVersCoordonnee(1, 5);
    CO_Coordonnee c7 = CO_NumeroCaseVersCoordonnee(7, 5);
    CU_ASSERT_FALSE(T_cheminExiste(terrain_test, c1, c7));
}

void test_pas_de_chemin_5_6(void) {
    CO_Coordonnee c5 = CO_NumeroCaseVersCoordonnee(5, 5);
    CO_Coordonnee c6 = CO_NumeroCaseVersCoordonnee(6, 5);
    CU_ASSERT_FALSE(T_cheminExiste(terrain_test, c5, c6));
}

void test_pas_de_chemin_diagonal_1_7(void) {
    CO_Coordonnee c1 = CO_NumeroCaseVersCoordonnee(1, 5);
    CO_Coordonnee c7 = CO_NumeroCaseVersCoordonnee(7, 5);
    CU_ASSERT_FALSE(T_cheminExiste(terrain_test, c1, c7));
}

/* -------------------------------------------------------------------------- */
/*                     TESTS : SYMÉTRIE DES CHEMINS                           */
/*                 (graphe non-orienté : A->B implique B->A)                  */
/* -------------------------------------------------------------------------- */

void test_symetrie_chemin_2_1(void) {
    CO_Coordonnee c1 = CO_NumeroCaseVersCoordonnee(1, 5);
    CO_Coordonnee c2 = CO_NumeroCaseVersCoordonnee(2, 5);
    // Si 1-2 existe, alors 2-1 doit exister aussi
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c2, c1));
}

void test_symetrie_chemin_11_6(void) {
    CO_Coordonnee c6 = CO_NumeroCaseVersCoordonnee(6, 5);
    CO_Coordonnee c11 = CO_NumeroCaseVersCoordonnee(11, 5);
    // Si 6-11 existe, alors 11-6 doit exister aussi
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c11, c6));
}

/* -------------------------------------------------------------------------- */
/*                    TESTS : CHEMINS SPÉCIFIQUES MAP.TXT                     */
/* -------------------------------------------------------------------------- */

void test_chemin_12_17(void) {
    CO_Coordonnee c12 = CO_NumeroCaseVersCoordonnee(12, 5);
    CO_Coordonnee c17 = CO_NumeroCaseVersCoordonnee(17, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c12, c17));
}

void test_chemin_12_13(void) {
    CO_Coordonnee c12 = CO_NumeroCaseVersCoordonnee(12, 5);
    CO_Coordonnee c13 = CO_NumeroCaseVersCoordonnee(13, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c12, c13));
}

void test_chemin_18_19(void) {
    CO_Coordonnee c18 = CO_NumeroCaseVersCoordonnee(18, 5);
    CO_Coordonnee c19 = CO_NumeroCaseVersCoordonnee(19, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c18, c19));
}

void test_chemin_18_23(void) {
    CO_Coordonnee c18 = CO_NumeroCaseVersCoordonnee(18, 5);
    CO_Coordonnee c23 = CO_NumeroCaseVersCoordonnee(23, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c18, c23));
}

void test_chemin_20_25(void) {
    CO_Coordonnee c20 = CO_NumeroCaseVersCoordonnee(20, 5);
    CO_Coordonnee c25 = CO_NumeroCaseVersCoordonnee(25, 5);
    CU_ASSERT_TRUE(T_cheminExiste(terrain_test, c20, c25));
}

/* -------------------------------------------------------------------------- */
/*                    TESTS : CONVERSION NUMÉRO <-> COORDONNÉE                */
/* -------------------------------------------------------------------------- */

void test_conversion_case_1(void) {
    CO_Coordonnee coord = CO_NumeroCaseVersCoordonnee(1, 5);
    CU_ASSERT_EQUAL(CO_abscisse(coord), 0);
    CU_ASSERT_EQUAL(CO_ordonnee(coord), 0);
    
    unsigned int num = CO_CoordonneeVersNumeroCase(coord, 5);
    CU_ASSERT_EQUAL(num, 1);
}

void test_conversion_case_13(void) {
    CO_Coordonnee coord = CO_NumeroCaseVersCoordonnee(13, 5);
    CU_ASSERT_EQUAL(CO_abscisse(coord), 2);
    CU_ASSERT_EQUAL(CO_ordonnee(coord), 2);
    
    unsigned int num = CO_CoordonneeVersNumeroCase(coord, 5);
    CU_ASSERT_EQUAL(num, 13);
}

void test_conversion_case_25(void) {
    CO_Coordonnee coord = CO_NumeroCaseVersCoordonnee(25, 5);
    CU_ASSERT_EQUAL(CO_abscisse(coord), 4);
    CU_ASSERT_EQUAL(CO_ordonnee(coord), 4);
    
    unsigned int num = CO_CoordonneeVersNumeroCase(coord, 5);
    CU_ASSERT_EQUAL(num, 25);
}

//============================================
//===============MAIN ========================
//============================================

int main(int argc, char** argv) {
    CU_pSuite pSuite_proprietes = NULL;
    CU_pSuite pSuite_objectifs = NULL;
    CU_pSuite pSuite_chemins = NULL;
    CU_pSuite pSuite_conversion = NULL;

    /* Initialisation du registre de tests */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* ===== Suite 1 : Propriétés du terrain ===== */
    pSuite_proprietes = CU_add_suite("Tests : Propriétés du terrain", init_suite_success, init_suite_success);
    if (NULL == pSuite_proprietes) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite_proprietes, "Taille du terrain", test_taille_terrain))
        || (NULL == CU_add_test(pSuite_proprietes, "Position de départ", test_position_depart))
        || (NULL == CU_add_test(pSuite_proprietes, "Direction de départ", test_direction_depart))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* ===== Suite 2 : Objectifs ===== */
    pSuite_objectifs = CU_add_suite("Tests : Objectifs", init_suite_success, init_suite_success);
    if (NULL == pSuite_objectifs) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite_objectifs, "Nombre d'objectifs", test_nombre_objectifs))
        || (NULL == CU_add_test(pSuite_objectifs, "Objectif case 13", test_objectif_case_13))
        || (NULL == CU_add_test(pSuite_objectifs, "Objectif case 22", test_objectif_case_22))
        || (NULL == CU_add_test(pSuite_objectifs, "Objectif case 20", test_objectif_case_20))
        || (NULL == CU_add_test(pSuite_objectifs, "Non-objectif case 1", test_non_objectif_case_1))
        || (NULL == CU_add_test(pSuite_objectifs, "Non-objectif case 25", test_non_objectif_case_25))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* ===== Suite 3 : Chemins ===== */
    pSuite_chemins = CU_add_suite("Tests : Chemins", 
                                  init_suite_success, init_suite_success);
    if (NULL == pSuite_chemins) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite_chemins, "Chemin 1-2", test_chemin_1_2))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 2-3", test_chemin_2_3))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 3-4", test_chemin_3_4))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 11-12", test_chemin_11_12))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 1-6", test_chemin_1_6))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 6-11", test_chemin_6_11))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 11-16", test_chemin_11_16))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 16-21", test_chemin_16_21))
        || (NULL == CU_add_test(pSuite_chemins, "Pas de chemin 1-3", test_pas_de_chemin_1_3))
        || (NULL == CU_add_test(pSuite_chemins, "Pas de chemin 1-7", test_pas_de_chemin_1_7))
        || (NULL == CU_add_test(pSuite_chemins, "Pas de chemin 5-6", test_pas_de_chemin_5_6))
        || (NULL == CU_add_test(pSuite_chemins, "Symétrie 2-1", test_symetrie_chemin_2_1))
        || (NULL == CU_add_test(pSuite_chemins, "Symétrie 11-6", test_symetrie_chemin_11_6))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 12-17", test_chemin_12_17))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 12-13", test_chemin_12_13))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 18-19", test_chemin_18_19))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 18-23", test_chemin_18_23))
        || (NULL == CU_add_test(pSuite_chemins, "Chemin 20-25", test_chemin_20_25))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* ===== Suite 4 : Conversions ===== */
    pSuite_conversion = CU_add_suite("Tests : Conversions numéro/coordonnée", 
                                     init_suite_success, init_suite_success);
    if (NULL == pSuite_conversion) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite_conversion, "Conversion case 1", test_conversion_case_1))
        || (NULL == CU_add_test(pSuite_conversion, "Conversion case 13", test_conversion_case_13))
        || (NULL == CU_add_test(pSuite_conversion, "Conversion case 25", test_conversion_case_25))
    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Lancement des tests */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    /* Nettoyage du registre */
    CU_cleanup_registry();
    return CU_get_error();
}
