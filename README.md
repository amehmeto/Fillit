# Fillit

Compiler avec :

main.c (obviously)
fillit.h
Libft/libft.a
fillit_is_sample_valid.c
fillit_encoder.c
fillit_resolver.c
fillit_displayer_no_color.c     ou    fillit_displayer_with_color.c

aka

gcc -Wall -Wextra -Werror fillit_is_sample_valid.c main.c Libft/libft.a fillit_encoder.c fillit_resolver.c fillit_displayer_with_color.c

Executer avec un fichier du dossier Sample.

Exemple :

    ./a.out Samples/26_valid_tetriminos.fillit
