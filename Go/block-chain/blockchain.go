package main

import (
    "fmt"
    "time"
    "crypto/sha256"
    "strconv"
    "bytes"
    "encoding/binary"
)

const (
    DIG_DIFFICULTY int = 2
)

type Block struct {
	Timestamp     int64
	Data          []byte
	PrevBlockHash []byte
	Hash          []byte
	Nonce         uint64
}

type BlockChain struct {
	blocks []*Block
}

func isValidHashDifficulty(hash string, difficulty int) bool {
	var cnt int
	for idx, ele := range hash {
		cnt = idx
		if (ele != 0) {
			break;
		}
	}
	return bool(cnt >= difficulty)
}

func Uint64ToByte(val uint64) []byte {
	var_str := make([]byte, 8)
	binary.BigEndian.PutUint64(var_str, val)
	return var_str
}

// 计算本区块的 hash 值
func (b *Block) SetHash() {
	timestamp := []byte(strconv.FormatInt(b.Timestamp, 10))
	nonce_str := Uint64ToByte(b.Nonce)
	headers := bytes.Join([][]byte{b.PrevBlockHash, b.Data, timestamp, nonce_str}, []byte{})
	hash := sha256.Sum256(headers)

	var nonce uint64
	for (!isValidHashDifficulty(string(hash[:]), DIG_DIFFICULTY)) {
		nonce = nonce + 1
		nonce_str := Uint64ToByte(nonce)
		newHeaders := bytes.Join([][]byte{b.PrevBlockHash, b.Data, timestamp, nonce_str},[]byte{})
		hash = sha256.Sum256(newHeaders)
	}

	b.Nonce = nonce
	b.Hash = hash[:]
}

// 新生成一个区块
func NewBlock(data string, hash[]byte) *Block {
	block := &Block {
		Timestamp: time.Now().Unix(),
		Data: []byte(data),
		PrevBlockHash: hash,
		Hash: []byte(""), 
		Nonce: 0,
	}
	block.SetHash()
	return block
}

// 生成创世区块
func NewGenesisBlock() *Block {
	block := NewBlock("Genesis Block", []byte{})
	return block
}

// 往区块链中加入区块
func (bc *BlockChain) AddBlock(data string) {
	prevBlock := bc.blocks[len(bc.blocks) - 1]
	newBlock := NewBlock(data, prevBlock.Hash)
	bc.blocks = append(bc.blocks, newBlock)
}

// 生成一个区块链
func NewBlockChain() *BlockChain {
	chain := &BlockChain{[]*Block{NewGenesisBlock()}}
	return chain
}

func main() {
	bc := NewBlockChain()
	bc.AddBlock("Send 1 BTC to titus")
	bc.AddBlock("Send 2 BTC to xiaoyi")

	for _, block := range bc.blocks {
		fmt.Printf("Pre hash: %x\n", block.PrevBlockHash)
		fmt.Printf("Data: %s\n", block.Data)
		fmt.Printf("Hash: %x\n", block.Hash)
		fmt.Printf("Nonce: %d\n", block.Nonce)

		fmt.Println()
	}
}
