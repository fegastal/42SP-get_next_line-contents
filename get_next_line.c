/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgastal- <fgastal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:51:37 by fgastal-          #+#    #+#             */
/*   Updated: 2022/05/09 00:33:17 by fgastal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" // Inclusão do header

char	*ft_strchr(const char *s, int c) // Função auxiliar para encontrar um caractere específico em uma string
{
	int	i; // Declaração de uma variavel (contador)

	i = 0; // Considerando-se que i vale 0 inicialmente (esteja na posição zero)
	if (!s) // Condição de segurança da string (não existir, por exemplo)
		return (0); // Retorna zero
	while (s[i]) // Enquanto o i pela string s não chegar ao fim ('\0')
	{
		if (s[i] == (char)c) // Se o i encontrar o caractere que procuramos ('\n')
			return ((char *)(s + i)); // Retornar o valor da string + o caractere
		i++; // Contador em i para continuar percorrendo a string
	}
	if (s[i] == (char)c) // Se o i chegar ao fim e encontrar o caractere que procuramos
		return ((char *)(s + i)); // Retornar o valor da string + caractere
	return (NULL); // Se nada disso acontecer, retornar nulo (erro)
}

static char	*get_comp(int fd, char *buffer,
char *accumulator, char *current_line) // Função complementar à principal, que será usada com recursividade naquela
{
	int		i; // Declaração da variável i (contador)

	i = 1; // Considerando-se que 1 seja igual a 1
	while (!ft_strchr(accumulator, '\n') && i) // Enquanto, com a função strch acima, nós NÃO encontrarmos o caractere '\n' e enquanto i não chegar ao fim
	{
		i = read(fd, buffer, BUFFER_SIZE);
		// Iremos chamar o system call "read" para armazenar o que há no file descriptor no buffer, a partir de um BUFFER_SIZE definido
		if (i == -1) // Considerando-se que i esteja na posição [-1], ou seja, antes de qualquer caractere
			return (NULL); // Retornaremos nulo
		if (!accumulator) // Se a string (local onde há armazenamento) não existir 
		{
			accumulator = (char *)malloc(1); // Iremos alocar memória para 1 byte (para um caractere)
			accumulator[0] = '\0'; // E a posição [0] da string terá o caractere '\0'
		}
		buffer[i] = '\0'; // Se na string (local de armazenamento) já existir e o i no buffer encontrar o '\0', ou seja, chegar no fim dele
		current_line = accumulator; // Iremos armazenar o que há no "accumulator" em "current_line"
		accumulator = ft_strjoin(current_line, buffer); // Depois disso, o accumulator irá obter o valor de retorno referente à união entre current_line e buffer, tudo o que houver ANTES da '\n'
		free(current_line); // Iremos liberar a memória presente em "current_line"
	}
	return (accumulator); // E iremos retornar o valor armazenado no accumulator
}

char	*get_next_line(int fd) // Função principal do nosso get_next_line.c, com um file descriptor com parâmetro e um retorno do tipo char
{
	static char	*accumulator; // Aqui, teremos uma variável de armazenamento (static char) chamada "accumulator"
	char		*buffer; // Um buffer para processamento de informação
	char		*current_line; // Um "current_line" para retorno do que há antes de uma quebra de linha

	if (read(fd, 0, 0) == -1) // Caso em que pode ocorrer um erro (no manual do read podemos obter essa informação)
		return (NULL); // Nesse caso em específico, retornar nulo;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); // Alocar memória o suficiente para o nosso espaço em BUFFER, a partir de um BUFFER_SIZE que será definido no header / na compilação;
	if (!buffer) // Se não houver nada no buffer;
		return (NULL); // Retornar nulo;
	current_line = NULL; // Considerando-se que, inicialmente, o espaço dentro da current_line eseja vazio;
	accumulator = get_comp(fd, buffer, accumulator, current_line); // Iremos aplicar a função get_comp na variável "accumulator" (onde tudo está sendo armazenado);
	free(buffer); // Iremos, portanto, liberar a memória que foi alocada dentro do buffer para que ele possa ser preenchido novamente;
	current_line = ft_strnldup(accumulator); // Iremos aplicar a função de strnldup, possuindo como parâmetro "accumulator" e armazenar o valor de retorno para "current_line"
	accumulator = verif(accumulator); // Iremos aplicar a função de verificação, possuindo como parâmetro o antigo "accumulator" e armazenar o valor de retorno para o novo "accumulator"
	return (current_line); // Retonar o valor de "current_line"
}
