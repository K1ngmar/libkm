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

# Clean up
.PHONY: clean fclean re

clean:
	@printf "$(COLOR_RED)"
	$(RM) -rf $(ODIR)
	@printf "$(COLOR_RESET)"

fclean: clean
	@printf "$(COLOR_RED)"
	$(RM) $(NAME)
	@printf "$(COLOR_RESET)"

re: fclean
	@$(MAKE) all

# Debugging
.PHONY: debug fsanitize

debug:
	@$(MAKE) re DEBUG=1

leaks:
	@$(MAKE) re LEAKS=1

fsanitize:
	@$(MAKE) re FSANITIZE=1
