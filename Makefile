SETTINGS_DIR := make_settings

include $(SETTINGS_DIR)/src.mk
include $(SETTINGS_DIR)/settings.mk
include $(SETTINGS_DIR)/colors.mk

all: $(NAME)

# Compilation
$(NAME): $(OBJ)
	@echo "$(COLOR_GREEN)Creating $(NAME) Library...$(COLOR_RESET)"
	@ar rcs $(NAME) $(OBJ)

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(TEST)/bin
	@mkdir -p $(@D)
	@echo "$(COLOR_LBLUE)Compiling...	$(COLOR_BLUE)$<$(COLOR_RESET)"
	@$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# testing

$(TEST)/bin/%: $(TEST)/%.c
	@echo "$(COLOR_LBLUE)Compiling tests... $(COLOR_BLUE)$<$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) $< $(OBJ) -o $@ -lcriterion $(ADDITIONAL_LIBRARIES)

test_build: $(NAME) $(TEST)/bin $(TESTBIN)

test: test_build
	@sh tests/run_tests.sh

# Clean up
.PHONY: clean fclean re

clean:
	@echo "$(COLOR_YELLOW)clean $(NAME)... $(COLOR_RESET)"
	@printf "$(COLOR_RED)"
	$(RM) -r $(ODIR)
	@printf "$(COLOR_RESET)"

fclean: clean
	@echo "$(COLOR_YELLOW)force clean $(NAME)... $(COLOR_RESET)"
	@printf "$(COLOR_RED)"
	$(RM) $(NAME)
	$(RM) -r $(TEST)/bin/*
	@printf "$(COLOR_RESET)"

re: fclean
	@$(MAKE) all

# Debugging
.PHONY: debug fsanitize

debug:
	@echo "$(COLOR_YELLOW)Building $(NAME) debug...	$(COLOR_RESET)"
	@$(MAKE) re DEBUG=1

leaks:
	@echo "$(COLOR_YELLOW)Building $(NAME) leaks...	$(COLOR_RESET)"
	@$(MAKE) re LEAKS=1

fsanitize:
	@echo "$(COLOR_YELLOW)Building $(NAME) fsanitize...	$(COLOR_RESET)"
	@$(MAKE) re FSANITIZE=1
