/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgastal- <fgastal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:51:37 by fgastal-          #+#    #+#             */
/*   Updated: 2022/05/05 21:25:35 by fgastal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" //Inclusão do header do GNL (lá estará presente o valor do BUFFER_SIZE);

// Nesse arquivo, temos a função principal chamada get_next_line e mais 3 funções auxiliares;
// O uso do ponteiro duplo é justificado pelo bônus (otimização apenas);

static char	*verif_buffer(char **storage, char **buffer, size_t buffer_len)
{
	// Função de verificação do buffer;
	char	*ret; // Variável de retorno;
	char	*tmp; // Variável temporária;
	size_t	i; // Variável para contador;
	
	i = ft_strlen(*storage);
	// Primeiro passo: passar para o meu i o tamanho do meu storage;
	// Se eu achei uma '\n' e há algo dentro do meu storage;
	// Então preciso concatenar as duas para resolver minha situação;
	// Para isso:
	// 1. Ver o tamanho da storage;
	// 2. Alocar memória para o retorno, que é para onde eu vou passar o valor todo;
	// 3. Com o memcpy, eu copio o valor no meu storage e depois eu ando até o fim do meu conteúdo,
	// com o i, então passo para lá o meu buffer com '\n'. Depois, coloco um '\0' para mostrar
	// que é até ali que eu quero pegar apenas.
	ret = (char *)malloc(sizeof(char) * (buffer_len + i + 1));
	// Aqui, estamos armazenando memória para o retorno;
	if (!ret) // Condição de segurança;
		return (NULL); // Retorna nulo;
	ft_memcpy(ret, *storage, i); // Aqui, eu copio a storage para o retorno;
	ft_memcpy(ret + i, *buffer, buffer_len); // Aqui, eu digo a posição final do buffer e passo para o retorno, copiando para depois concatenar;
	ret [i + buffer_len] = '\0'; // Passando o caractere de fim de linha para o retorno;
	tmp = ft_strdup((*buffer) + buffer_len); // Duplicando e passando para a temporária;
	if (*storage) // Se houver algo dentro da storage;
		free (*storage); // Liberar a memória;
	(*storage) = tmp; // Se não houver algo na storage, pegar o que há presente na tmp;
	return (ret); // Retornar o que houver lá;
}

static char	*put_storage(char **storage, char **buffer, size_t i)
{
	// Função responsável pela armazenagem na storage (acumuladora);
	// Observação: usado o duplo pointer para reutilizar para o bônus;
	char	*tmp; // Declaração de variável temporária;
	char	*ret; // Declaração de variável de retorno;

	ret = NULL; // Declarando inicialmente que o retorno seja nulo;
	if (i <= 0) //Se o i for negativo ou nulo, ou seja, significa que não há mais nada para ler, então vou simplesmente LIMPAR a storage;
	{
		if (i == 0 && *storage) //Se não há nada para ler, então passar o que sobrou para a storage e retornar o que houver lá;
		{
			ret = (*storage); // Passando para o retorno o que há na storage;
			*storage = NULL; // Reinicializa a storage com um null;
		}
		return (ret); // Retorna;
	}
	(* buffer)[i] = '\0'; // Caractere de fim de uma linha;
	// No while da função principal, passo um read para a variável i;
	// Ou seja, passo o quanto ele vai ler para o i;
	// Então, depois, coloco um NULL para definir até ONDE ele vai ler;
	// Na variável tmp, vou olhar para o buffer até achar uma \n;
	// E, depois, vou jogar na tmp;
	// Se eu achar o \n, vou para uma função de verificação de buffer;
	tmp = ft_strchr(*buffer, '\n'); // Procura pelo \n no buffer através da função strchr;
	if (tmp) // Se existir um '\n' na variável temporária;
		ret = verif_buffer(storage, buffer, (tmp - *buffer) + 1);
		// Faremos uma verificação no buffer a partir da diferença do que há na temporária para o buffer e acrescentamos 1;
		// Daí isso vai ser vinculado ao retorno;
	else // Se não existir um '\n' na temporária;
	{
		tmp = ft_strjoin(*storage, *buffer); // Faremos um strjoin entre storage e buffer;
		if (*storage) // Se não estiver vazia;
			free (*storage); // Liberamos a memória que há na storage;
		*storage = tmp; // Associamos o que há na tmp na storage;
	}
	// Se não for o caso de nada disso;
	return (ret); // Retornamos o valor de retorno;
}

static char	*verif_storage(char **storage, size_t size)
{
	// Nessa função, apenas verificaremos a situação do storage;
	// Se eu já achei um '\n', para o sistema identificar isso, preciso colocar um '\0' no fim da frase para retorná-la;
	char	*tmp; // Para isso, usaremos uma variável temporária;
	char	*ret; // A variável de retorno;
	size_t	i; // Um contador de caracteres;

	if (size < 0) // Condição de segurança
		return (NULL); // Retornamos nulo em caso de erro;
	ret = (char *)malloc(sizeof(char) * size + 1); // Se não der erro, ou seja, o size for > 0;
	// Aqui, vamos alocar memória para o retorno, a partir de size + 1 ('\0' no fim);
	if (!ret) // Condição de segurança, caso o retorno não exista ou dê erro;
		return (NULL); // Retorna nulo;
	i = -1; // Somente para economizar linha com a incrementação em ++i;
	while (++ i != size) // Enquanto não chegar ao fim (no tamanho total);
		ret[i] = (*storage)[i]; // Aqui, vou passando tudo o que houver no storage para o meu retorno;
	ret[i] = '\0'; // Depois, coloco um caractere nulo no fim, para poder retornar;
	tmp = ft_strdup(*storage + i); // Na variável temporária, chamamos a função de duplicação, para que o que há ANTES do '\n' seja passado
	// para o retorno, sem prejudicar o que há depois (para não perder informação);
	free (*storage); // Liberamos, portanto, a memória alocada na storage
	(*storage) = tmp; // Deixamos apenas o que há DEPOIS do '\n', presente em tmp;
	return (ret); // Retornamos isso;
}

char	*get_next_line(int fd)
{
// Minha função principal possui um file descriptor como parâmetro
// É a partir dela que vou chamando as funções auxiliares
	static char	*storage;
	// Essa variável precisa ser necessariamente estática para poder MANTER o valor que for acumulado no storage
	char		*buffer;
	// Onde será processada a informação do file content transformado em file descriptor pelo open no main.c
	char		*ret;
	// Onde tudo será retornado;
	size_t		i;
	// Variável para percorrer o file content 
	
	if((read(fd, 0, 0) == -1) || (fd < 0 || fd > 1024) || BUFFER_SIZE <= 0)
	// Aqui temos três condições separadas por "ou"
	// A primeira é que, se read (com os parâmetros especificados) for igual a -1, será erro (contido no manual)
	// A segunda são os máximos e mínimos de um file descriptor (valores foram pesquisados)
	// A terceira é que o BUFFER_SIZE não pode ser negativo ou igual a 0, precisamos passar um valor positivo para ele ser lido
	// Ou seja, se contiver esses erros (condição de segurança):
		return (0);
	// Caso nenhum desses erros específicos ocorram...
	i = 1; // Declarando que a variável que percorrerá o texto inicie em 1;
	ret = NULL; // Declarando que inicialmente nosso retorno será zero;
	buffer = ft_strchr(storage, '\n'); // Verificar se na storage há caracteres '\n' através da função ft_strchr;
	if (!buffer) //Se não encontrarmos o '\n'
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); //type cast para que o buffer seja do tipo char
		// Nessa parte, estamos alocando memória suficiente para o tamanho do buffer + 1 ('\0');
		// Se, mesmo assim, ainda não encontrarmos o '\n' no buffer;
		if (!buffer) // Condição de segurança;
			return(0);
		while (ret == NULL && i > 0) // Enquanto o retorno for nulo e o i for maior que 0 (segurança);
		{
			i = read(fd, buffer, BUFFER_SIZE);
			// Para a variável i, vou estar passando o system call read e lerei o que há no meu arquivo fd;
			// int = read(int fd, void *buffer, int count);
			// Lembrando que meu BUFFER_SIZE é definido no header;
			ret = put_storage(&storage, &buffer, i); // Nessa função auxiliar, acontecerá a verificação de buffer para achar o \n. 
			// Se não encontrar (ou encontrar), vai fazer o strjoin entre o buffer e o storage;
		}
		free(buffer); // Quando encontrar um \n no storage a partir do join, vamos liberar a memória alocada e retornar o valor;
		return (ret); // Retornamos o valor
	}
	// Aqui, se encontrarmos logo o '\n' no buffer, fazemos o verif_storage
	ret = verif_storage(&storage, (buffer - storage) + 1); // Vamos jogar para o retorno tudo o que há ANTES do '\n' armanezado no storage;
	return (ret); // A linha irá ser retornada e tudo aquilo que há DEPOIS do '\n' continuará armazenado na variável estática, para que possa ser reutilizado na geração da próxima linha;
}
