# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Nome do executável final
TARGET = teste

# Diretório dos objetos
OBJDIR = build

# Fontes (.c)
SRC = teste.c $(FILE)

# Converte "arquivo.c" → "build/arquivo.o"
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

# Regra padrão
all: $(TARGET)

# Cria o executável a partir dos objetos
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(OBJDIR)/$(TARGET)

# Regra para compilar cada .c em .o (colocando os .o dentro de build/)
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria a pasta build se não existir
$(OBJDIR):
	mkdir $(OBJDIR)

# Limpar tudo
clean:
	rm -rf $(OBJDIR) $(TARGET)
