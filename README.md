./pipex infile "cmd1 cmd1-options?" "cmd2 cmd2-options?" outfile

0) access (infile)
1) cmd1 -> exists?
2) exec (cmd1 cmd1-options?)
	execv: (["cm1", "-la"])
	execv: **args
	Cria um novo processo para executar o comando
	Com base no retorno de execv (tratamento de erro)
		success <- 0
		erro <- != 0
			acessar a msg de erro (wait)?
				consultar errno com perror.. resgatar!

Conceitos...? YouTube

	0) como funciona o pipe?
	1) fork? Cria um sub-processo
	2) processo?
	4) como usar a função dup2?
	5) como funciona a função wait
	6) execv - executar (os inputs) em outro processo (1)
	7) dup2 - redirecionamento do STDOUT do processo filho
	pro pipe

main ----(wait)-------(end wait, com algum retorno)-------
		\              /
	fork --------------