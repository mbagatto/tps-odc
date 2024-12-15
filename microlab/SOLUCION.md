# Secuenciales

**1. ¿Cuáles son y qué representa cada entrada y cada salida del componente? ¿Cuáles entradas deben ser consideradas como de control?**
#### Entradas

- **clk**: representa los pulsos del *clock*. Cuando es `1`, tenemos flanco positivo, y cuando es `0` flanco negativo.

- **w**: es una entrada de control. Cuando tengamos un pulso de clock y esta entrada valga `1`, nos va a permitir almacenar el valor de `Reg_in` en el *flip-flop D*. En el caso que valga `0` no se almacenará nada ya que la compuerta *AND* no activará la entrada de clock del *flip-flop D*.

- **Reg_in**: representa el valor de entrada que se almacenará en el *flip-flop D*.

- **en_out**: es una entrada de control. Al habilitarla, `Reg_output` tomará el valor que está almacenado en el *flip-flop D*.

#### Salidas

- **Reg_output**: representa el valor que está almacenado en el *flip-flop D*. Tomará algún valor determinado cuando la señal `en_out` esté habilitada.

- **Reg_Debug**: también representa el valor que está almacenado en el *flip-flop D*, pero no tiene en cuenta el `en_out`. Por su nombre, intuimos que puede llegar a servir para verificar el estado interno del *flip-flop D*.

**2. Las entradas `input_bit` y `en_input_bit` sirven para poder introducir en el circuito un valor arbitrario. Escribir una secuencia de activación y desactivación de entradas para que el registro `R1` pase a tener el valor `1`.**

![](/imagenes/wavedrom2.png)

**3. Dar una secuencia de activaciones que inicialmente ponga un valor `1` en `R0`, luego que este valor se transfiera a `R1`, luego que el valor de `R2` pase a `R0` y finalmente el valor de `R1` a `R2`.**

![](/imagenes/wavedrom3.png)

# OrgaSmall

### 1. Análisis

**¿Cuál es el tamaño de la memoria?**
- La memoria puede almacenar hasta 256 palabras de 8 bits cada una, lo que da un total de 2048 bits o 256 bytes.

**¿Qué tamaño tiene el `PC`?**
- El tamaño del `PC` es de 1 byte.

**¿Cuántas instrucciones nuevas se podrían agregar respetando el formato de instrucción indicado?**
- Teniendo en cuenta que el `CodOp` está formado por 5 bits, se pueden representar hasta 32 códigos de operación distintos. Por lo tanto, respetando las 22 instrucciones ya existentes (entre ellas la instrucción *fetch* que tiene como código de operación `00000`), se podrían agregar **10** nuevas instrucciones. Los códigos de operación que quedan disponibles son: `01001`, `01010`, `01011`, `01100`, `01101`, `01110`, `01111`, `11100`, `11101` y `11110`.

**¿Qué función cumple la señal `inc` de el `PC`?**
- Esta señal es la encargada de incrementar en *1* el `PC`. En general, el `PC` será incrementado durante el ciclo de instrucción *fetch*.

**¿Qué función cumple la señal `opW` de la `ALU`?**
- Esta señal está presente en los registros de cada flag dentro de la `ALU`, controlando su salida. Cuando está encendida, permite que pase el valor de cada flag.

**¿Para qué sirve la señal `DE_enOutImm`? ¿Qué parte del circuito indica que registro se va a leer y escribir?**
- Esta señal se utiliza en las instrucciones relacionadas con una dirección de memoria. Es la encargada de habilitar la entrada al bus del valor inmediato.

**¿Cómo se resuelven los saltos condicionales en la `ControlUnit`? Describir el mecanismo.**
- Si alguna de las señales `jc_microOp`, `jz_microOp` o `jn_microOp` está encendida, estamos queriendo ejecutar un salto condicional, con lo cuál, requerimos que a su vez esté encendido el flag correspondiente (por ejemplo si `jc_microOp` está encendido, para poder ejecutar este salto condicional, debe también estar encendido el flag `C`). Si se cumplen estas dos condiciones, el `microPC` será incrementado en *2* y se saltea la línea de `reset_microOp`, cargando en el `PC` la dirección de memoria que tenía la instrucción. Finalmente, `reset_microOp` hace un *fetch*. En el caso en que no se cumplan las condiciones, el `microPC` será incrementado en *1* y caerá en la línea siguiente del microcódigo, que está `reset_microOp`, y hace un *fetch* de la instrucción siguiente.

### 2. Ensamblar y correr

**Antes de correr el programa, identificar el comportamiento esperado.**
- En primer lugar, se espera que el programa empiece a partir de la línea cuya etiqueta es `seguir`. En este paso, se setean los valores de los registros `R0` y `R1` en *0xFF* y *0x11* respectivamente. La siguiente instrucción etiquetada por `siguiente` va a hacer la suma entre `R0` y `R1`, y guardará el resultado en `R0`. Mientras el flag de carry esté encendido, se repetirá este procedimiento. El programa finalizará cuando no se detecte carry.

**¿Qué lugar ocupará cada instrucción en la memoria? Detallar por qué valor se reemplazarán las etiquetas.**
- `JMP seguir` ocupará las direcciones `00` y `01` en la memoria.
- `SET R0, 0xFF` ocupará las direcciones `02` y `03` en la memoria.
- `SET R1, 0x11` ocupará las direcciones `04` y `05` en la memoria.
- `ADD R0, R1` ocupará las direcciones `06` y `07` en la memoria.
- `JC siguiente` ocupará las direcciones `08` y `09` en la memoria.
- `JMP halt` ocupará las direcciones `0A` y `0B` en la memoria.

Las etiquetas `seguir`, `siguiente` y `halt` tomarán los valores `02`, `06` y `0A` respectivamente. El código con los valores reemplazados de las etiquetas quedaría:
```assembly
JMP 02

SET R0, 0xFF
SET R1, 0x11

ADD R0, R1
JC 06

JMP 0A
```

**Ejecutar y controlar ¿cuántos ciclos de clock son necesarios para que este código llegue a la instrucción JMP halt?**
- Se llega a la instrucción `JMP halt` luego de **53** ciclos de clock.

**¿Cuántas microinstrucciones son necesarias para realizar el ADD? ¿Cuántas para el salto?**
- Para realizar el `ADD` son necesarias las siguientes **5** microinstrucciones:
```ops
RB_enOut  ALU_enA  RB_selectIndexOut=0 (1)
RB_enOut  ALU_enB  RB_selectIndexOut=1 (2)
ALU_OP=ADD ALU_opW                     (3)
RB_enIn   ALU_enOut RB_selectIndexIn=0 (4)
reset_microOp                          (5)
```
- Para realizar el `JMP` son necesarias las siguientes **2** microinstrucciones:
```ops
PC_load DE_enOutImm                    (1)
reset_microOp                          (2)
```