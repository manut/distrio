MAKE_DIRECTORIES = io/lib common manager/lib devices io/bin manager/bin

.PHONY: all
idl: $(MAKE_DIRECTORIES)
all: $(MAKE_DIRECTORIES)

.PHONY: $(MAKE_DIRECTORIES)
$(MAKE_DIRECTORIES):
	@$(MAKE) --keep-going --directory=$@ $(MAKECMDGOALS)

.PHONY: $(MAKECMDGOALS)
$(MAKECMDGOALS): $(MAKE_DIRECTORIES)
