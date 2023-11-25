package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
)

type HuffmanNode struct {
	freq        int
	order       int
	value       rune
	left, right *HuffmanNode
}

func (self HuffmanNode) Freq() int {
	return self.freq
}

func (self HuffmanNode) Order() int {
	return self.order
}

type treeHeap []*HuffmanNode

// Implementação das funções da interface heap.Interface
func (th treeHeap) Len() int {
	//fmt.Println("my Len")
	return len(th)
}
func (th treeHeap) Less(i, j int) bool {
	if th[i].Freq() == th[j].Freq() {
		return th[i].Order() < th[j].Order()
	}
	return th[i].Freq() < th[j].Freq()
}

func (th *treeHeap) PushWithOrder(ele *HuffmanNode) {
	index := len(*th)
	//fmt.Println("Index: ", index)
	for i, node := range *th {
		if ele.Freq() < node.Freq() {
			index = i
			//fmt.Println("Novo Index: ", index)
			break
		}
	}
	*th = append((*th)[:index], append([]*HuffmanNode{ele}, (*th)[index:]...)...)
	// imprimir o elemento que foi inserido e seu elemento da esquerda e direita
	if index > 0 {
		//fmt.Printf("Elemento inserido: %c\t%d\t%d\n", ele.value, ele.freq, ele.order)
		//fmt.Printf("Elemento a esquerda: %c\t%d\t%d\n", (*th)[index-1].value, (*th)[index-1].freq, (*th)[index-1].order)
		// fmt.Printf("Frequencia:%d\t Simbolo:%c\t Ordem:%d\nFrequencia:%d\t Simbolo:%c\t Ordem:%d \n", ele.Freq(), ele.value, ele.order, (*th)[index-1].Freq(), (*th)[index-1].value, (*th)[index-1].order)
	}
}

func (th *treeHeap) RemoveFirst() interface{} {
	if len(*th) == 0 {
		return nil
	}
	primeiroElemento := (*th)[0]
	*th = (*th)[1:]
	return primeiroElemento
}

func (th treeHeap) Swap(i, j int) { th[i], th[j] = th[j], th[i] }

func buildTree(trees treeHeap) HuffmanNode {
	for trees.Len() > 1 {
		a := trees.RemoveFirst().(*HuffmanNode)
		b := trees.RemoveFirst().(*HuffmanNode)
		//fmt.Printf("Frequencia:%d\t Simbolo:%c\t Ordem:%d\nFrequencia:%d\t Simbolo:%c\t Ordem:%d \n", a.Freq(), a.value, a.order, b.Freq(), b.value, b.order)
		trees.PushWithOrder(&HuffmanNode{a.Freq() + b.Freq(), a.order + b.order, 0, a, b})
		//fmt.Println("Fila após a inserção:")
		//printHeap(trees)
	}
	return *trees[0] // Retorna a raiz da árvore de Huffman
}

// Imprime a fila de prioridade
func printHeap(trees treeHeap) {
	for _, tree := range trees {
		fmt.Printf("%c\t%d\t%d\n", tree.value, tree.freq, tree.order)
	}
}

// função para construir a codificação de Huffman
func buildCodes(tree HuffmanNode, prefix []byte, codes map[rune]string) {
	if tree.value != 0 {
		// Se é uma folha, adicione o símbolo e seu código ao mapa
		codes[tree.value] = string(prefix)
	} else {
		// Percorre a esquerda adicionando '0' ao prefixo
		prefix = append(prefix, '0')
		buildCodes(*tree.left, prefix, codes)
		prefix = prefix[:len(prefix)-1]

		// Percorre a direita adicionando '1' ao prefixo
		prefix = append(prefix, '1')
		buildCodes(*tree.right, prefix, codes)
		prefix = prefix[:len(prefix)-1]
	}
}

// Função auxiliar para inicializar e chamar buildCodes
func printCodes(tree HuffmanNode) map[rune]string {
	codes := make(map[rune]string)
	buildCodes(tree, []byte{}, codes)
	return codes
}

// função para salvar odicionario da codificacao de Huffman em um arquivo
func save_file(codes map[rune]string, nome_arquivo string) error {
	// Cria o arquivo
	arquivo, err := os.Create(nome_arquivo)
	if err != nil {
		log.Fatal(err)
		return err // Retorna o erro se houver algum
	}
	defer arquivo.Close()

	// Escreve no arquivo
	for simbolo, codigo := range codes {
		arquivo.WriteString(fmt.Sprintf("%c:%s\n", simbolo, codigo))
	}

	return nil
}

// função pra codificar a frase
func codificar_frase(conteudo string, codes map[rune]string) string {
	var frase_codificada string
	for _, simbolo := range conteudo {
		frase_codificada += codes[simbolo]
	}
	return frase_codificada
}

// função para salvar a frase codificada em um arquivo
func save_file_codificado(codificado string, nome_arquivo string) error {
	// Cria o arquivo
	arquivo, err := os.Create(nome_arquivo)
	if err != nil {
		log.Fatal(err)
		return err // Retorna o erro se houver algum
	}
	defer arquivo.Close()

	// Escreve no arquivo a frase codificada em binário
	for _, bit := range codificado {
		arquivo.WriteString(fmt.Sprintf("%c", bit))
	}

	return nil
}

// função que le o arquivo e retorna um map com os símbolos e suas frequências
func read_file(nome_arquivo string) (string, error) {
	// Abre o arquivo
	arquivo, err := os.Open(nome_arquivo)
	if err != nil {
		log.Fatal(err)
		return "", err // Retorna o erro se houver algum
	}
	defer arquivo.Close()

	// Usa um scanner para ler o arquivo e constrói uma string com o conteúdo
	var conteudo string
	// Lê o arquivo
	scanner := bufio.NewScanner(arquivo)
	scanner.Split(bufio.ScanRunes)
	for scanner.Scan() {
		conteudo += scanner.Text()
	}
	if err := scanner.Err(); err != nil {
		log.Fatal(err)
		return "", err
	}
	return conteudo, nil
}

func count_symbol_construct_queot(conteudo string) treeHeap {
	var trees treeHeap
	frequencias := make(map[rune]HuffmanNode)
	ordem := 0

	for _, simbolo := range conteudo {
		if simbolo != '\n' {
			node, ok := frequencias[simbolo]
			if !ok {
				node = HuffmanNode{freq: 1, order: ordem, value: simbolo}
				frequencias[simbolo] = node
				ordem++
			} else {
				node.freq++
				frequencias[simbolo] = node
			}
		}
	}

	for _, node := range frequencias {
		nodeCopy := node                 // Criar uma cópia do node
		trees = append(trees, &nodeCopy) // Anexar a cópia, não o original
	}

	sort.Slice(trees, func(i, j int) bool {
		if trees[i].freq != trees[j].freq {
			return trees[i].freq < trees[j].freq
		}
		return trees[i].order < trees[j].order
	})

	return trees
}

// função para calcular a taxa de compressão considerando
func taxa_compressao(conteudo string, codes map[rune]string) float64 {
	var tamanho_original, tamanho_comprimido int
	for _, simbolo := range conteudo {
		tamanho_original++
		tamanho_comprimido += len(codes[simbolo])
	}
	fmt.Printf("Tamanho original: %d\n", tamanho_original * 8)
	fmt.Printf("Tamanho comprimido: %d\n", tamanho_comprimido)
	return float64(tamanho_comprimido) / (float64(tamanho_original) * 8)
}

// Driver program to test above functions
func main() {
	// caminho do arquivo relatívo ao arquivo huffman.go subindo um diretório
	caminho := "../arquivos/arquivo.txt"
	conteudo, err := read_file(caminho)
	if err != nil {
		log.Fatal(err)
	}

	symFreqs := count_symbol_construct_queot(conteudo)
	//fmt.Println("SYMBOL\tWEIGHT\tORDER")
	//printHeap(symFreqs)
	huffmanTree := buildTree(symFreqs)

	//construir a codificação de Huffman
	codes := printCodes(huffmanTree)

	// salvar a codificação de Huffman em um arquivo
	err = save_file(codes, "../arquivos/codificacao.txt")

	// codificar a frase
	codificado := codificar_frase(conteudo, codes)

	if err != nil {
		log.Fatal(err)
	}
	// salvar a frase codificada em um arquivo
	err = save_file_codificado(codificado, "../arquivos/codificado.txt")

	if err != nil {
		log.Fatal(err)
	}

	// calcular a taxa de compressão
	taxa := taxa_compressao(conteudo, codes)
	fmt.Printf("Taxa de compressão: %.2f\n", taxa)
}
