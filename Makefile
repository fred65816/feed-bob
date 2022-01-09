SRC_DIR = src
BIN_DIR = bin

.PHONY: exec clean source

exec: source bindir
	cp $(SRC_DIR)/game $(BIN_DIR)
	rm $(SRC_DIR)/game

bindir:
	mkdir -p $(BIN_DIR)

clean:
	$(MAKE) clean -C $(SRC_DIR)
	rm -rf $(BIN_DIR)

source:
	$(MAKE) -C $(SRC_DIR)
