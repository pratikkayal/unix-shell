unix-shell: modular_shell shell.c
	gcc shell.c -o shell

modular_shell: shell.c
	gcc modular_shell.c -o modular_shell -l readline

modularshell: shell.c
	gcc modular_shell.c -o modular_shell -l readline

clean:
	rm shell myshell modular_shell
