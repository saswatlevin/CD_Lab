flex tokenizer.l 
gcc -g lex.yy.c -o tokenizer -lfl
./tokenizer
gcc -g q1.c -o q1
./q1