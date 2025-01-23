package tree_sitter_herl_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_herl "github.com/williamthome/tree-sitter-herl/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_herl.Language())
	if language == nil {
		t.Errorf("Error loading HErl grammar")
	}
}
