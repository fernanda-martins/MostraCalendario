#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numberOfDays(int monthNumber, int year) { //retorna o numero de dias no mes
  
    if (monthNumber == 0) //janeiro
        return (31);
 
    if (monthNumber == 1) { // leap year if perfectly divisible by 400
      if (year % 400 == 0) {
        return 29;
      }
      // not a leap year if divisible by 100 but not divisible by 400
      else if (year % 100 == 0) {
        return 28;
      }
      // leap year if not divisible by 100 but divisible by 4
      else if (year % 4 == 0) {
        return 29;
      }
      // all other years are not leap years
      else {
        return 28;
      }
  }

  if (monthNumber == 2)
    return (31);

  if (monthNumber == 3)
    return (30);

  if (monthNumber == 4)
    return (31);

  if (monthNumber == 5)
    return (30);

  if (monthNumber == 6)
    return (31);

  if (monthNumber == 7)
    return (31);

  if (monthNumber == 8)
    return (30);

  if (monthNumber == 9)
    return (31);

  if (monthNumber == 10)
    return (30);

  if (monthNumber == 11)
    return (31);

  return 0;
}

void gerarCalendario(int calendario[6][7], int qntDias, int inicioDoMes) {
  int contador = 1;
  int start = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      if (start || inicioDoMes == j) {
        start = 1;
        if (contador <= qntDias) {
          calendario[i][j] = contador;
          contador += 1;
        } else {
          calendario[i][j] = 0;
        }
      } else {
        calendario[i][j] = 0;
      }
    }
  }
}

void printCalendario(int calendario[6][7]) {
  printf("  D  S  T  Q  Q  S  S\n");
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      printf(" %2d", calendario[i][j]); // printa com espaçador
    }
    printf("\n");
  }
}

int main(int argc, char **argv) {
  time_t rawtime;
  struct tm *timeinfo;
  int year, month, day;
  int matriz_mes[6][7];

  time(&rawtime);
  timeinfo = localtime(&rawtime); // hoje
  timeinfo->tm_mday = 1;
  rawtime = mktime(timeinfo); // milisegundos
  timeinfo = localtime(&rawtime);

  // ---------------------------------------------------(MES ATUAL)
  if (argc == 1) { // calendario - mês corrente do ano corrente
    int qntDias = numberOfDays(timeinfo->tm_mon, timeinfo->tm_year);
    int inicioDoMes = timeinfo->tm_wday;
    gerarCalendario(matriz_mes, qntDias, inicioDoMes);
    printCalendario(matriz_mes);
    exit(0);
  }
  // ----------------------------------------------------(12 MESES)

  if (argc == 2) { // calendario 2000 - passando o ano - mostra os 12 meses -looping ate 12
    year = atoi(argv[1]);
    timeinfo->tm_mday = 1;
    timeinfo->tm_year = year-1900;
    for (int i = 0; i < 12; i++) {
      timeinfo->tm_mon = i;       // numero do mes
      rawtime = mktime(timeinfo); // milisegundos
      timeinfo = localtime(&rawtime);
      int qntDias = numberOfDays(timeinfo->tm_mon, timeinfo->tm_year);
      int inicioDoMes = timeinfo->tm_wday;
      gerarCalendario(matriz_mes, qntDias, inicioDoMes);
      printCalendario(matriz_mes);
      printf("-----------------------------\n");
    }
    exit(0);
  }

  // -----------------------------------------------------(MES QUE PEDIU)

  if (argc == 3) { // calendario 10 2000 - mostra aquele mes
    month = atoi(argv[1]);
    year = atoi(argv[2]);
    
    if (month < 1 || month > 12) {
      printf("Erro!\nMes invalido!");
      exit(1);
    } 
      
    timeinfo->tm_mday = 1;
    timeinfo->tm_mon = month - 1;
    timeinfo->tm_year = year - 1900;
    
    rawtime = mktime(timeinfo); // milisegundos
    timeinfo = localtime(&rawtime);
    
    int qntDias = numberOfDays(timeinfo->tm_mon, timeinfo->tm_year);
    int inicioDoMes = timeinfo->tm_wday;
    gerarCalendario(matriz_mes, qntDias, inicioDoMes);
    printCalendario(matriz_mes);
    exit(0);
    
  } else {
    printf("Erro!\nUso do programa: exemplo dia mes ano, todos inteiros");
    exit(1);
  }

  return 0;
}
