
# Organisation des sources.

export SRCDIR = mqueue
export BINDIR = bin

SUBDIRS = $(SRCDIR)

#
# Définitions des outils.
#

# Compilateur.
export CC = gcc
# options de compilation
export CCFLAGS += -O0 
# avec debuggage : -g -DDEBUG
# sans debuggage : -DNDEBUG
export CCFLAGS += -DNDEBUG
 # gestion automatique des dépendances
export CCFLAGS += -MMD -MP
export CCFLAGS += -D_BSD_SOURCE -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE -D_DEFAULT_SOURCE -D_GNU_SOURCE
#On compile en utilisant les options de gcc
export CCFLAGS += -std=c99 -Wall
# -pedantic retiré car génère des warnings pour mes TRACE
export LDFLAGS += -lrt -pthread

#
# Définitions du binaire à générer.
#
export PROG = $(BINDIR)/robot_pc

#
# Règles du Makefile.
#

# Compilation récursive.
all: 
	@for i in $(SUBDIRS); do (cd $$i; make $@); done

# Nettoyage.
.PHONY: clean

clean:
	@for i in $(SUBDIRS); do (cd $$i; make $@); done
	@rm -f $(PROG) core* $(BINDIR)/core*

