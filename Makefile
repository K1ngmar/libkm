SETTINGS_DIR := make_settings

include $(SETTINGS_DIR)/src.mk
include $(SETTINGS_DIR)/settings.mk
include $(SETTINGS_DIR)/colors.mk

all:
	@$(MAKE) $(NAME)

# Compilation
$(NAME): $(OBJ)
	@echo "$(COLOR_GREEN)Creating Library...$(COLOR_RESET)"
	@ar rcs $(NAME).a $(OBJ)

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(@D)
	@echo "$(COLOR_LBLUE)Compiling...	$(COLOR_BLUE)$<$(COLOR_RESET)"
	@$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# testing

$(TEST)/bin/%: $(TEST)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) $< $(OBJ) -o $@ -lcriterion

test: fclean $(TEST)/bin $(TESTBIN)
	@for test in $(TESTBIN) ; do ./$$test ; done

# Clean up
.PHONY: clean fclean re

clean:
	@printf "$(COLOR_RED)"
	$(RM) -r $(ODIR)
	@printf "$(COLOR_RESET)"

fclean: clean
	@printf "$(COLOR_RED)"
	$(RM) $(NAME)
	$(RM) -r $(TEST)/bin/*
	@printf "$(COLOR_RESET)"

re: fclean
	@$(MAKE) all

# Debugging
.PHONY: debug fsanitize

debug:
	@$(MAKE) test DEBUG=1

leaks:
	@$(MAKE) test LEAKS=1

fsanitize:
	@$(MAKE) test FSANITIZE=1
