/**
 * @file functions.h
 * @brief Definicoes das funcoes principais
 * \par
 * Contem as assinaturas de algumas funcoes utilizadas\n
 * Contem as macros das cores utilizadas:\n
 *   YELLOW = titulos\n
 *   BLUE = botoes/seletores\n
 *   RED = desvantagem\n
 *   GREEN = vantagem\n
 *   L BLUE = texto relevante\n
 *   DEFAULT = texto normal\n
 *   ROXO = inativo\n
 *   BOLD = destaques menores\n
 * @author Joao Victor
 */
#ifndef __COLORS__
#define C_BLUE "\e[1;36m"
#define C_RED "\e[1;31m"
#define C_GREEN "\e[1;32m"
#define C_L_BLUE "\e[1;34m"
#define C_YELLOW "\e[1;33m"
#define C_DEFAULT "\e[0m"
#define C_ROXO "\e[35m"
#define C_BOLD "\e[1;37m"
#endif

#ifndef __FUNCTIONSH__
#define __FUNCTIONSH__

int start();

int elem_beat(char* elem1, char* elem2);

Ninja* fight(Ninja* ninja_one, Ninja* ninja_two, int attribute);

#endif