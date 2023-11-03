package main
 
import (
    "bufio"
    "container/heap"
    "fmt"
    "log"
    "os"
)
 
type HuffmanTree interface {
    Freq() int
}
 
type HuffmanLeaf struct {
    freq  int
    value rune
}
 
type HuffmanNode struct {
    freq        int
    left, right HuffmanTree
}
 
func (self HuffmanLeaf) Freq() int {
    return self.freq
}
 
func (self HuffmanNode) Freq() int {
    return self.freq
}
 
type treeHeap []HuffmanTree
 
func (th treeHeap) Len() int { return len(th) }
func (th treeHeap) Less(i, j int) bool {
    return th[i].Freq() < th[j].Freq()
}
func (th *treeHeap) Push(ele interface{}) {
    *th = append(*th, ele.(HuffmanTree))
}
func (th *treeHeap) Pop() (popped interface{}) {
    popped = (*th)[len(*th)-1]
    *th = (*th)[:len(*th)-1]
    return
}
func (th treeHeap) Swap(i, j int) { th[i], th[j] = th[j], th[i] }

func buildHeap(symFreqs map[rune]int) treeHeap {
    var trees treeHeap
    for c, f := range symFreqs {
        trees = append(trees, HuffmanLeaf{f, c})
    }
    heap.Init(&trees)
    return trees
}

func buildTree(trees treeHeap) HuffmanTree {
    for trees.Len() > 1 {
        a := heap.Pop(&trees).(HuffmanTree)
        b := heap.Pop(&trees).(HuffmanTree)
        // imprimir frequências e o simbolo
        fmt.Printf("%d: %c\t%d: %c\n", a.Freq(), a.(HuffmanLeaf).value, b.Freq(), b.(HuffmanLeaf).value)
        //fmt.Println(a.Freq(), b.Freq())
        heap.Push(&trees, HuffmanNode{a.Freq() + b.Freq(), a, b})
    }
    return heap.Pop(&trees).(HuffmanTree)
}

func printHeap(trees treeHeap) {
    for _, tree := range trees {
        switch i := tree.(type) {
        case HuffmanLeaf:
            fmt.Printf("%c\t%d\n", i.value, i.freq)
        case HuffmanNode:
            fmt.Printf("%d\n", i.Freq())
        }
    }
}

// Imprime os códigos de Huffman a partir da raiz da árvore de Huffman. Usa byte[] para armazenar os códigos
func printCodes(tree HuffmanTree, prefix []byte) {
    switch i := tree.(type) {
    case HuffmanLeaf:
        // Se esse é um nó folha, então ele contém um dos caracteres de entrada, imprime o caractere e seu código de byte[]
        fmt.Printf("%c\t%d\t%s\n", i.value, i.freq, string(prefix))
    case HuffmanNode:
        // Assina 0 para a borda esquerda e recorre
        prefix = append(prefix, '0')
        printCodes(i.left, prefix)
        prefix = prefix[:len(prefix)-1]
 
        // Assina 1 para a borda direita e recorre
        prefix = append(prefix, '1')
        printCodes(i.right, prefix)
        prefix = prefix[:len(prefix)-1]
    }
}

// função que le o arquivo e retorna um map com os símbolos e suas frequências
func ler_arquivo(nome_arquivo string) (string, error) {
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
// função para contar a frequência de cada símbolo no conteúdo
func conta_simbolos(conteudo string) map[rune]int {
    // Cria um mapa para armazenar as frequências
    frequencias := make(map[rune]int)

    // Conta a frequência de cada símbolo
    for _, simbolo := range conteudo {
        if simbolo != '\n' {
            frequencias[simbolo]++
        }
    }
    return frequencias
}

// Driver program to test above functions
func main() {
    // caminho do arquivo
    caminho := "arquivos/arquivo.txt"
    conteudo, err := ler_arquivo(caminho)
	if err != nil {
		log.Fatal(err)
	}
 
    symFreqs := conta_simbolos(conteudo)
    trees := buildHeap(symFreqs)
    printHeap(trees)
    huffmanTree := buildTree(trees)
 
    // example tree
    //exampleTree := buildTree(symFreqs)
 
    // print out results
    fmt.Println("SYMBOL\tWEIGHT\tHUFFMAN CODE")
    printCodes(huffmanTree, []byte{})
}