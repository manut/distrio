MAKE_DIRECTORIES = common manager

.PHONY: all
all: $(MAKE_DIRECTORIES)

.PHONY: $(MAKE_DIRECTORIES)
$(MAKE_DIRECTORIES):
	@$(MAKE) --keep-going --directory=$@ $(MAKECMDGOALS)

.PHONY: $(MAKECMDGOALS)
$(MAKECMDGOALS): $(MAKE_DIRECTORIES)
