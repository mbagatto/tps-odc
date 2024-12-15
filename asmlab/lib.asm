
global strClone
global strPrint
global strCmp
global strLen
global strDelete

global arrayNew
global arrayDelete
global arrayPrint
global arrayGetSize
global arrayAddLast
global arrayGet
global arrayRemove
global arraySwap

global cardCmp
global cardClone
global cardAddStacked
global cardDelete
global cardGetSuit
global cardGetNumber
global cardGetStacked
global cardPrint
global cardNew

section .data
null db 'NULL', 0
openBrace db '[', 0
coma db ',', 0
closeBrace db ']', 0
openBracket db '{', 0
dash db '-', 0
closeBracket db '}', 0

section .text
extern malloc
extern fprintf
extern free
extern getCloneFunction
extern getDeleteFunction
extern getPrintFunction
extern intCmp
extern intClone
extern intPrint
extern intDelete
extern listNew
extern listClone
extern listPrint
extern listAddFirst
extern listDelete

ARRAY_OFF_TYPE EQU 0
ARRAY_OFF_SIZE EQU 4
ARRAY_OFF_CAPACITY EQU 5
ARRAY_OFF_DATA EQU 8
ARRAY_SIZE EQU 16
ARRAY_DATA_SIZE EQU 8

CARD_OFF_SUIT EQU 0
CARD_OFF_NUMBER EQU 8
CARD_OFF_STACKED EQU 16
CARD_SIZE EQU 24

; ** String **
;char* strClone(char* a);
strClone:
    push rbp
    mov rbp, rsp
    push r12
    sub rsp, 8

    mov r12, rdi
    call strLen
    inc eax ;para tener en cuenta el byte \0
    mov rdi, rax
    call malloc
    ; en rax tengo el puntero
    mov rdi, r12
    mov rcx, rax

    .while:
        cmp [rdi], byte 0
        je .end
        xor rsi, rsi
        mov sil, [rdi]
        mov [rcx], sil
        inc rcx
        inc rdi
        jmp .while

    .end:
        mov [rcx], byte 0
        add rsp, 8
        pop r12
        pop rbp
        ret

;void strPrint(char* a, FILE* pFile)
strPrint:
    push rbp
    mov rbp, rsp

    cmp [rdi], byte 0
    je .null
    jmp .notnull

    .null:
        mov rdi, null ; rdi = "NULL"
        mov r8, rdi ; r8 = "NULL"
        mov rdi, rsi ; rdi = pFile
        mov rsi, r8 ; rsi = "NULL"
        call fprintf ; fprintf(rdi, rsi) = fprintf(pFile, "NULL")
        jmp .end

    .notnull:
        mov r8, rdi ; r8 = a
        mov rdi, rsi ; rdi = pFile
        mov rsi, r8 ; rsi = a
        call fprintf ; fprintf(rdi, rsi) = fprintf(pFile, a)

    .end:
        pop rbp
        ret

;uint32_t strLen(char* a);
strLen:
    push rbp
    mov rbp, rsp
    push r12
    sub rsp, 8
    mov r12, 0 ; r12 va a ser el contador

    .while:
    mov dl, [rdi + r12] ; dl = a[i]
    inc r12
    cmp dl, 0
    jne .while

    dec r12 ; le resto 1 para no contar el \0
    mov eax, r12d

    .end:
        add rsp, 8
        pop r12
        pop rbp
        ret

;int32_t strCmp(char* a, char* b);
strCmp:
    push rbp
    mov rbp, rsp
    push r12
    push rbx
    mov rax, 0

    .while:
        mov r12b, [rdi] ; r12b = a[i]
        mov bl, [rsi] ; bl = b[i]
        cmp r12b, bl
        jne .notEqual

        cmp r12b, 0
        jz .notEqual

        inc rdi
        inc rsi
        jmp .while

    .notEqual:
        jg .aIsHigher
        jl .bIsHigher
        jmp .end

    .aIsHigher:
        mov rax, -1
        jmp .end

    .bIsHigher:
        mov rax, 1
        jmp .end

    .end:
        pop rbx
        pop r12
        pop rbp
        ret

;void strDelete(char* a);
strDelete:
    push rbp
    mov rbp, rsp

    call free ; free(a)

    .end:
        pop rbp
        ret

; ** Array **

; uint8_t arrayGetSize(array_t* a)
arrayGetSize:
    push rbp
    mov rbp, rsp

    mov rax, 0
    mov al, [rdi + ARRAY_OFF_SIZE] ; al = a->size

    .end:
        pop rbp
        ret

; void arrayAddLast(array_t* a, void* data)
arrayAddLast:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    sub rsp, 8

    mov r12, rdi ; r12 = a
    mov r13, rsi ; r13 = data
    mov r14, [rdi + ARRAY_OFF_DATA] ; r14 = a->data

    mov sil, [rdi + ARRAY_OFF_SIZE] ; sil = a->size
    cmp sil, [rdi + ARRAY_OFF_CAPACITY]
    jge .end

    mov rdi, 0
    mov edi, [r12] ; edi = a->type
    call getCloneFunction
    mov rbp, rax

    mov rdi, r13
    call rbp

    mov rdx, 0
    mov dl, [r12 + ARRAY_OFF_SIZE]
    mov [r14 + rdx*ARRAY_OFF_DATA], rax
    inc byte [r12 + ARRAY_OFF_SIZE]

    .end:
        add rsp, 8
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

; void* arrayGet(array_t* a, uint8_t i)
arrayGet:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r15
    sub rsp, 8

    mov r12, 0
    mov r15, 0

    mov r12b, byte [rdi + ARRAY_OFF_SIZE] ; r12b = a->size
    mov r13, [rdi + ARRAY_OFF_DATA] ; r13 = a->data
    mov r15b, sil ; r15b = i

    .checkRange:
        cmp r12, r15 ; (a->size == i)
        jbe .outOfRange
        jae .inRange

    .inRange:
        mov rax, [r13 + r15*8] ; rax = data[i]
        jmp .end

    .outOfRange:
        mov rax, 0

    .end:
        add rsp, 8
        pop r15
        pop r13
        pop r12
        pop rbp
        ret

; array_t* arrayNew(type_t t, uint8_t capacity)
arrayNew:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push rbx
    sub rsp, 8

    mov r12, rdi ; type_t t
    mov r13b, sil ; uint8_t capacity

    mov rdi, ARRAY_SIZE
    call malloc
    mov rbx, rax

    mov dword [rbx + ARRAY_OFF_TYPE], r12d ; inicializo type
    mov byte [rbx + ARRAY_OFF_SIZE], 0 ; inicializo size
    mov byte [rbx + ARRAY_OFF_CAPACITY], r13b ; inicializo capacity

    .dataPointer:
        mov rdi, 0
        mov rsi, 0
        mov sil, byte [rbx + ARRAY_OFF_CAPACITY]
        mov rax, 0
        add rax, 8
        add dil, sil
        mul rdi
        mov rdi, rax
        call malloc
        ; rax tiene el puntero a los datos del array
    mov [rbx + ARRAY_OFF_DATA], rax
    mov rax, rbx

    .end:
        add rsp, 8
        pop rbx
        pop r13
        pop r12
        pop rbp
        ret

; void* arrayRemove(array_t* a, uint8_t i)
arrayRemove:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    push r15
    push rbx
    mov rbx, 0
    mov r15, 0
    mov r13, 0
    sub rbp, 8

    mov r14, rdi ; r14 = array_t* a
    mov r12b , [r14 + ARRAY_OFF_SIZE] ; r12b = a->size
    mov r13,  [r14 + ARRAY_OFF_DATA] ; r13 = a->data
    mov r15b , sil ; r15b = i

    cmp r12b, r15b ; (a->size == i)
    jbe .outOfRange

    mov rax, [r13 + r15*8] ; rax = a[i]

    .compare:
        inc r15 ; r15 = i+1
        cmp r15b, r12b ; (i+1 == a->size)
        jne .reposition
        jmp .resize


    .reposition:
        cmp r15b, r12b
        jae .resize
        mov ebx, [r13 + r15*8]
        mov [r13 +  (r15*8 - 8)], ebx
        inc r15
        jmp .reposition

    .resize:
        dec r12
        mov [r14 + ARRAY_OFF_SIZE], r12b
        jmp .end

    .outOfRange:
        mov rax, 0
        jmp .end

    .end:
        add rbp, 8
        pop rbx
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

; void arraySwap(array_t* a, uint8_t i, uint8_t j)
arraySwap:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r13, 0
    mov r8, 0
    mov r9, 0

    mov r12, rdi ; r12 = array_t* a
    mov r13d, [rdi + ARRAY_OFF_SIZE] ; r13d = a->size
    mov r8b, sil ; r8b = i
    mov r9b, dl ; r9b = j

    .compare:
        cmp r8b, r9b ; (i == j)
        je .end

        cmp r8b, r13b ; (i == a->size)
        jae .end

        cmp r9b, r13b ; (j == a->size)
        jae .end

    .swap:
        mov r12, [rdi + ARRAY_OFF_DATA] ; r12 = a->data
        mov r10, [r12 + r8*8] ; r10 = data[i]
        mov r11, [r12 + r9*8] ; r11 = data[j]

        mov [r12 + r8*8], r11 ; data[i] = data[j]
        mov [r12 + r9*8], r10 ; data[j] = data[i]

    .end:
        pop r13
        pop r12
        pop rbp
        ret

; void arrayDelete(array_t* a) {
arrayDelete:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    sub rsp, 8

    mov r13, 0

    mov r12, rdi ; r12 = array_t* a
    mov r13b, byte [r12 + ARRAY_OFF_SIZE] ; r13b = a->size
    mov edi, [r12 + ARRAY_OFF_TYPE] ; edi = a->type
    call getDeleteFunction
    mov r14, rax ; r14 = deleteFunc

    .empty:
        cmp r13d, 0
        je .deleteStruct

    .notEmpty:
        dec r13 ; r13 = a->size - 1
        mov rdi, r12 ; rdi = a
        mov rsi, r13 ; rsi = a->size
        call arrayRemove
        mov rdi, rax
        call r14
        jmp .empty

    .deleteStruct:
        mov rdi, [r12 + ARRAY_OFF_DATA] ; rdi = a->data
        call free
        mov rdi, r12 ; rdi = a
        call free

    .end:
        add rsp, 8
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

;void arrayPrint(array_t* a, FILE* pFile)
arrayPrint:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    push r15

    mov r14, 0
    mov r12, rdi ; r12 = array_t* a
    mov r13, rsi ; r13 = pFile

    mov edi, [r12 + ARRAY_OFF_TYPE] ; edi = a->type
    call getPrintFunction
    mov r15, rax ; r15 = printFunc

    .printOpenBrace:
        mov rdi, rsi ; rdi = pFile
        mov rsi, openBrace ; rsi = "["
        call fprintf

    .compare:
        mov rcx, 0
        mov cl, [r12 + ARRAY_OFF_SIZE] ; cl = a->size
        cmp rcx, r14
        jz .printCloseBrace

    .while:
        mov r8, [r12 + ARRAY_OFF_DATA] ; r8 = a->data
        mov rdi, [r8 + r14*8] ; rdi = data[i]
        mov rsi, r13 ; rsi = pFile
        call r15
        inc r14 ; r14 = i + 1
        mov rcx, 0
        mov cl, [r12 + ARRAY_OFF_SIZE] ; cl = a->size
        cmp rcx, r14 ; (a->size == i + 1)
        jz .printCloseBrace

    .printComa:
        mov rdi, r13 ; rdi = pFile
        mov rsi, coma ; rsi = ","
        call fprintf
        jmp .compare

    .printCloseBrace:
        mov rdi, r13 ; rdi = pFile
        mov rsi, closeBrace ; rsi = "]"
        call fprintf

    .end:
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

; ** Card **

; card_t* cardNew(char* suit, int32_t* number)
cardNew:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push rbx
    sub rsp, 8

    mov r12, 0
    mov r13, 0
    mov rbx, 0

    mov r12, rdi ; r12b = suit
    mov r13, rsi ; r13d = number

    .structInit:
        mov edi, CARD_SIZE
        call malloc
        mov rbx, rax

    .suitInit:
        mov rdi, r12
        call strClone
        mov [rbx + CARD_OFF_SUIT], rax

    .numberInit:
        mov rdi, r13
        call intClone
        mov [rbx + CARD_OFF_NUMBER], rax

    .stackedInit:
        mov edi, 3 ; edi = CardType
        call listNew
        mov [rbx + CARD_OFF_STACKED], rax

    mov rax, rbx

    .end:
        add rsp, 8
        pop rbx
        pop r13
        pop r12
        pop rbp
        ret

;char* cardGetSuit(card_t* c)
cardGetSuit:
    push rbp
    mov rbp, rsp

    mov rax, [rdi + CARD_OFF_SUIT]

    .end:
        pop rbp
        ret

;int32_t* cardGetNumber(card_t* c)
cardGetNumber:
    push rbp
    mov rbp, rsp

    mov rax, [rdi + CARD_OFF_NUMBER]

    .end:
        pop rbp
        ret

;list_t* cardGetStacked(card_t* c)
cardGetStacked:
    push rbp
    mov rbp, rsp

    mov rax, [rdi + CARD_OFF_STACKED]

    .end:
        pop rbp
        ret

;void cardPrint(card_t* c, FILE* pFile)
cardPrint:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi ; r12 = card_t* c
    mov r13, rsi ; r13 = pFile

    .printOpenBracket:
        mov rdi, r13 ; rdi = pFile
        mov rsi, openBracket ; rsi = "{"
        call fprintf

    .printSuit:
        mov rdi, r12 ; rdi = c
        call cardGetSuit
        mov rdi, rax
        mov rsi, r13 ; rsi = pFile
        call strPrint

    .printDash:
        mov rdi, r13 ; rdi = pFile
        mov rsi, dash ; rsi = "-"
        call fprintf


    .printNumber: ;void intPrint(int32_t *a, FILE *pFile)
        mov rdi, r12 ; rdi = c
        call cardGetNumber
        mov rdi, rax ; rdi = number
        mov rsi, r13 ; rsi = pFile
        call intPrint

    .printSecondDash:
        mov rdi, r13 ; rdi = pFile
        mov rsi, dash ; rsi = "-"
        call fprintf

    .printStacked: ;void listPrint(list_t *l, FILE *pFile)
        ;mov rdi, r12 ; rdi = stacked
        ;mov rsi, r13 ; rsi = pFile
        ;call listPrint
        mov rdi, r12
        call cardGetStacked
        mov rdi, rax
        mov rsi, r13
        call listPrint

    mov rdi, r13 ; rdi = pFile
    mov rsi, closeBracket ; rsi = "}"
    call fprintf

    .end:
        pop r13
        pop r12
        pop rbp
        ret

;int32_t cardCmp(card_t* a, card_t* b)
cardCmp:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    sub rsp, 8

    mov r12, rdi ; r12 = a
    mov r13, rsi ; r13 = b

    .compareSuit:
        call cardGetSuit
        mov r14, rax ; r14 = a->suit
        mov rdi, r13 ; rdi = b
        call cardGetSuit
        mov rsi, rax ; rsi = b->suit
        mov rdi, r14 ; rdi = a->suit
        call strCmp
        test rax, rax
        jz .compareNumber
        jmp .end

    .compareNumber:
        mov rdi, r12 ; rdi = a
        call cardGetNumber
        mov r14, rax ; r14 = a->number
        mov rdi, r13 ; rdi = b
        call cardGetNumber
        mov rsi, rax ; rsi = b->number
        mov rdi, r14 ; rdi = a->number
        call intCmp

    .end:
        add rsp, 8;
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

;card_t* cardClone(card_t* c)
cardClone:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi ; r12 = c

    mov rdi, CARD_SIZE
    call malloc
    mov r13, rax

    mov rdi, r12 ; rdi = c
    call cardGetSuit
    mov rdi, rax ; rdi = c->suit
    call strClone
    mov [r13 + CARD_OFF_SUIT], rax

    mov rdi, r12 ; rdi = c
    call cardGetNumber
    mov rdi, rax ; rdi = c->number
    call intClone
    mov [r13 + CARD_OFF_NUMBER], rax

    mov rdi, r12 ; rdi = c
    call cardGetStacked
    mov rdi, rax ; rdi = c->stacked
    call listClone
    mov [r13 + CARD_OFF_STACKED], rax

    mov rax, r13

    .end:
        pop r13
        pop r12
        pop rbp
        ret

;void cardAddStacked(card_t* c, card_t* card)
cardAddStacked:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rsi ; r12 = card

    call cardGetStacked
    mov rdi, rax ; rdi = c->stacked
    mov rsi, r12 ; rsi = card
    call listAddFirst

    .end:
        pop r13
        pop r12
        pop rbp
        ret

;void cardDelete(card_t* c)
cardDelete:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    push r15

    mov r12, 0
    mov r13, 0
    mov r14, 0
    mov r15, 0

    mov r12, rdi ; r12 = c
    mov r13, [r12 + CARD_OFF_SUIT] ; r13 = c->suit
    mov r14, [r12 + CARD_OFF_NUMBER] ; r13 = c->number
    mov r15, [r12 + CARD_OFF_STACKED] ; r13 = c->stacked

    .deleteSuit:
        mov rdi, r13 ; rdi = c->suit
        call strDelete
        jmp .deleteNumber

    .deleteNumber:
        mov rdi, r14 ; rdi = c->number
        call intDelete
        jmp .deleteStacked

    .deleteStacked:
        mov rdi, r15 ; rdi = c->stacked
        call listDelete
        jmp .deleteStruct

    .deleteStruct:
        mov rdi, r12 ; rdi = c
        call free
        jmp .end

    .end:
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret
