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

static char	*get_nl(int fd, char *buffer, char *str, char *save) // Função complementar à principal, que será usada com recursividade
{
	int		i; // Declaração da variável i (contador)

	i = 1; // Considerando-se que 1 seja igual a 1
	while (!ft_strchr(str, '\n') && i) // Enquanto, com a função strch acima, nós NÃO encontrarmos o caractere '\n' e enquanto i não chegar ao fim
	{
		i = read(fd, buffer, BUFFER_SIZE); // Iremos chamar o system call "read" para armazenar o que há no file descriptor no buffer, a partir de um BUFFER_SIZE definido
		if (i == -1) // Considerando-se que i esteja na posição [-1], ou seja, antes de qualquer caractere
			return (NULL); // Retornaremos nulo
		if (!str) // Se a string (local onde há armazenamento) não existir 
		{
			str = (char *)malloc(1); // Iremos alocar memória para 1 byte (para um caractere)
			str[0] = '\0'; // Se na posição [0] da string já houver um '\0'
		}
		buffer[i] = '\0'; // Se a string (local de armazenamento) já existir e o i no buffer encontrar o '\0', ou seja, chegar no fim dele
		save = str; // Iremos armazenar o que há na str (armazenamento) em save
		str = ft_strjoin(save, buffer); // Depois disso, a str irá obter o valor de retorno referente à união entre save e buffer, tudo o que houver ANTES da '\n'
		free(save); // Iremos liberar a memória presente em "save"
	}
	return (str); // E iremos retornar o valor armazenado em str
}

char	*get_next_line(int fd)  // Função principal do nosso get_next_line.c, com um file descriptor com parâmetro e um retorno do tipo char
{
	static char	*str; // Aqui, teremos uma variável de armazenamento (static char) chamada str;
	char		*buffer; // Um buffer para processamento de informação;
	char		*save; // Um save para retorno do que há antes de uma quebra de linha;

	if (read(fd, 0, 0) == -1) // Caso em que pode ocorrer um erro (no manual do read podemos obter essa informação)
		return (NULL); // Nesse caso em específico, retornar nulo;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); // Alocar memória o suficiente para o nosso espaço em BUFFER, a partir de um BUFFER_SIZE que será definido no header / na compilação;
	if (!buffer) // Se não houver nada no buffer;
		return (NULL); // Retornar nulo;
	save = NULL; // Considerando-se que, inicialmente, o espaço dentro do save eseja vazio;
	str = get_nl(fd, buffer, str, save); // Iremos aplicar a função get_nl na variável str (onde tudo está sendo armazenado);
	free(buffer); // Iremos, portanto, liberar a memória que foi alocada dentro do buffer para que ele possa ser repreenchido;
	save = ft_strnldup(str); // Iremos aplicar a função de strnldup, possuindo como parâmetro 'str' e armazenar o valor de retorno para 'save'
	str = ft_exstrchr(str); // Iremos aplicar a função de ft_exstrchr, possuindo como parâmetro o antigo 'str' e armazenar o valor de retorno para o novo 'str'
	return (save); // Retonar o valor de 'save'
}
