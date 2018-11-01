# pcs3868-sistemas-computacao-alto-desempenho

Repositório para os trabalhos da disciplina PCS3868 de @epiceric e @mateusnakajo.

## Docker

```bash
docker build -t epiceric/hpc .
docker run -ti -v $PWD:/root/src epiceric/hpc
```

### MPI

Exemplo:

```bash
mpicc -o exercicio exercicio.c
mpirun -np 4 $PWD/exercicio
```
