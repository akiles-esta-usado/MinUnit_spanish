# MinUnit - Framework extremadamente simple para Unit Testing en C
http://www.jera.com/techinfo/jtns/jtn002.html

Este archivo es una burda traducción con apuntes personales. El enlace indicado redirige al documento original.

## Introducción
Los Frameworks de testing son muy populares en el mundo de la programación orientada a objetos.
Algunos ejemplos de frameworks ampliamente ocupados que ofrecen una extensa funcionalidad son:

- JUnit para Java
- SUnit para Smalltalk
- CppUnit para C++

Sin embargo, esto puede ser intimidante para quienes quieran realizar testing en entornos restringidos, como un sistema embebido.
MinUnit es un framework de testing extremadamente simple escrito en C que consta de 2 macros y no hace uso de asignación de memoria, por lo que debería funcionar bajo cualquier entorno.

## Código Fuente
    /* file: minunit.h */
    extern int tests_run;

    #define mu_assert(message, test) \
        do {                         \
            if (!(test))             \
                return message;      \
        } while (0)

    #define mu_run_test(test)        \
        do {                         \
            char *message = test();  \
            tests_run++;             \
            if (message)             \
                return message;      \
        } while (0)

El código puede caber perfectamente en 3 lineas, solo lo expando para que sea más legible.

### mu_assert(message, test)
Retorna un string si la expresión entregada es falsa.

### mu_runtest(test)
Invoca un test y retorna su mensaje si este falla.

### tests_run
Contador de tests que se han realizado.

## Como hacer un Test Case
Un TestCase de MinUnit consiste en una función que retorna 0 si el test pasa.
Si el test falla, la función retorna un string que describe la causa.
Es la función que ocupa la macro `mu_assert`.

Un TestSuite, la función que invoca los TestCases, ocupa `mu_runtest` para ejecutar los tests.

Se utiliza una función main para ejecutar el TestSuite. Si este falla imprime el mensaje retornado.

## Ejemplos
### minunit_example
Este ejemplo realiza dos tests, uno pasa y el otro no.

    /* file: minunit_example.c */
    #include <stdio.h>
    #include "minunit.h"
 
    int tests_run = 0;
 
    int foo = 7;
    int bar = 4;
 
    static char * test_foo() {
        mu_assert("error, foo != 7", foo == 7);
        return 0;
    }
 
    static char * test_bar() {
        mu_assert("error, bar != 5", bar == 5);
        return 0;
    }
 
    static char * all_tests() {
        mu_run_test(test_foo);
        mu_run_test(test_bar);
        return 0;
    }
 
    int main(int argc, char **argv) {
        char *result = all_tests();

        if (result != 0)
            printf("%s\n", result);

        else
            printf("ALL TESTS PASSED\n");

        printf("Tests run: %d\n", tests_run);
 
        return result != 0;
    }

### Ejemplo Preprocesado
Además de preprocesarlo, eliminé los `do {} while` en los TestCases, en `all_tests` no fue posible, y también indenté según mi criterio estético.

    /* gcc -E minunit_example.c (editado) */
    int tests_run = 0;

    int foo = 7;
    int bar = 4;

    static char * test_foo() {
        if (!(foo == 7)) 
            return "error, foo != 7"; 

        return 0;
    }

    static char * test_bar() {
    if (!(bar == 5)) 
        return "error, bar != 5"; 

    return 0;
    }

    static char * all_tests() {
        do { 
            char *message = test_foo();
            tests_run++; 
            
            if (message) 
                return message; 
        } while (0);
        
        do { 
            char *message = test_bar(); 
            tests_run++; 
            
            if (message) 
                return message; 
        } while (0);
    
        return 0;
    }

    int main(int argc, char **argv) {
        char *result = all_tests();

        if (result != 0)
            printf("%s\n", result);

        else 
            printf("ALL TESTS PASSED\n");

        printf("Tests run: %d\n", tests_run);

        return result != 0;
    }

### not_so_simpler
En este código verifico una función, `adder.c`, e incluyo el código fuente directamente en el test.
Esto es una práctica común al hacer testing dado que en ocaciones se mantiene un estado o ocupan funciones internas que no se muestran en la interfaz que provee la cabecera.

## Licencia
Yo la verdad no cacho mucho de licencias, pero el agradable sujeto que escribio este framework indica lo siguiente:

> You may use the code in this tech note for any purpose, with the understanding that it comes with NO WARRANTY.

## Apéndices
Se ocupa `do {} while(0)` porque es recomendable para macros que tienen más de una sentencia, es como una buena práctica.
Para más información, revisar: 

> http://c-faq.com/cpp/multistmt.html

El uso de funciones `static` simplemente límita el scope de las funciones a este archivo o, más correctamente, a esta 'translation unit'.
