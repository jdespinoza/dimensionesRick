// tercera dimansion del proyecto 2
// FileSystem
//Operativos
// Jason Espinoza y Jose Miguel Hernandez

#define FUSE_USE_VERSION 26
#define _XOPEN_SOURCE 500
#define RFS_DATA ((struct rfs_struct *) fuse_get_context()->private_data)

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>

// Estructura del File System
struct rfs_struct {
    char *root;
};


// Se encarga de revisar los permisos para que el usuario ejecute una accion
// Tambien construye el PATH_MAX completo para el directorio raiz
static void rfs_getcompletePath(char completePath[PATH_MAX], const char *path) {
   strcpy(completePath, RFS_DATA->root);
   strncat(completePath, path, PATH_MAX);
}

// Esta funcion se encarga de obtener los atributos de un archivo
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_getattr(const char *path, struct stat *st) {
   printf("--> Realizando el getattr\n");
   int status = 0;
   char completePath[PATH_MAX];
   st->st_blksize = 4096;//se define el tamano del bloque
   rfs_getcompletePath(completePath, path);
   status = lstat(completePath, st); // se encarga de obtener la informacion del archivo
   if (status != 0) {
     printf("--> Error a la hora de realizar el getattr\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de crear un directorio
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_mkdir(const char *path, mode_t mode) {
   printf("--> Realizando el mkdir\n");
   int status = 0;
   char completePath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   status = mkdir(completePath, mode);//se encarga de crear el directorio
   if (status < 0) {
     printf("--> Error a la hora de realizar el mkdir\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de eliminar un archivo
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_unlink(const char *path) {
   printf("--> Realizando el unlink\n");
   int status = 0;
   char completePath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   status = unlink(completePath);//se encarga de eliminar el archivo
   if (status < 0) {
     printf("--> Error a la hora de realizar el unlink\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de eliminar un directorio
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_rmdir(const char *path) {
   printf("--> Realizando el rmdir\n");
   int status = 0;
   char completePath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   status = rmdir(completePath);//se encarga de borrar el directorio
    if (status < 0) {
      printf("--> Error a la hora de realizar el rmdir\n");
      status = -errno;
    }
    return status;
}

// Esta funcion se encarga de renombrar un archivo
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_rename(const char *path, const char *newpath) {
   printf("--> Realizando el rename\n");
   int status = 0;
   char completePath[PATH_MAX];
   char fullPath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   rfs_getcompletePath(fullPath, newpath);
   status = rename(completePath, fullPath);//se encarga de renombrar el archivo
   if (status < 0) {
     printf("-->  Error a la hora de realizar el rename\n");
     status = -errno;
   }
   return status;
}

// Cambia los tiempos de modificacion y el acceso de un archivo
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_utime(const char *path, struct utimbuf *ubuf) {
   printf("--> Realizando el utime\n");
   int status = 0;
   char completePath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   status = utime(completePath, ubuf);// esta funcion se encarga de modificar los valores
   if (status < 0) {
     printf("--> Error a la hora de realizar el utime\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de abrir un archivo
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_open(const char *path, struct fuse_file_info *fi) {
   printf("--> Realizando el open\n");
   int status = 0;
   int fd;
   char completePath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   fd = open(completePath, fi->flags);//se encarga de abrir el archivo
   if (fd < 0) {
     printf("--> Error a la hora de realizar el open\n");
     status = -errno;
   }
   fi->fh = fd;
   return status;
}

// Esta funcion se encarga de leer de un archivo
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi) {
   printf("--> Realizando el read\n");
   int status = 0;
   status = pread(fi->fh, buffer, size, offset);//se encarga de realizar la lectura
   if (status < 0) {
     printf("--> Error a la hora de realizar el read\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de escribir en un archivo
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_write(const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *fi) {
   printf("--> Realizando el write\n");
   int status = 0;
   status = pwrite(fi->fh, buffer, size, offset);//se encarga de realizar la escritura
   if (status < 0) {
     printf("--> Error a la hora de realizar el write\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de obtener estadisticas del file system
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_statfs(const char *path, struct statvfs *statv) {
   printf("--> Realizando el statfs\n");
   int status = 0;
   char completePath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   status = statvfs(completePath, statv);//se encarga de obtener las estadisticas
   if (status < 0) {
     printf("--> Error en statfs\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de sincronizar los contenidos de un archivo del fs
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
   printf("--> Realizando el fsync\n");
   int status = 0;
   if (datasync) {//comprueba que el valor exista
     status = fdatasync(fi->fh);
   }
   else	{
     status = fsync(fi->fh);
   }
   if (status < 0) {
     printf("--> Error a la hora de realizar el fsync\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de abrir un directorio
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_opendir(const char *path, struct fuse_file_info *fi) {
   printf("--> Realizando el opendir\n");
   DIR *directory;
   int status = 0;
   char completePath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   directory = opendir(completePath);//se encarga de abrir el directorio
   if (directory == NULL) {
     printf("--> Error a la hora de realizar el opendir\n");
     status = -errno;
   }
   fi->fh = (intptr_t) directory;
   return status;
}

// Esta funcion se encarga de hacer lectura sobre un directorio
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
   printf("--> Realizando el readdir\n");
   int status = 0;
   DIR *directory;
   struct dirent *dirStr;
   directory = (DIR*) (uintptr_t) fi->fh;
   dirStr = readdir(directory);//se encarga de leer el directorio
   if (dirStr == 0) {
     printf("--> Error a la hora de realizar el readdir\n");
      status = -errno;
      return status;
   }
   do {
      if (filler(buffer, dirStr->d_name, NULL, 0) != 0) {
	       return -ENOMEM;
      }
   } while ((dirStr = readdir(directory)) != NULL);
   return status;
}

// Inicializa la estructura de datos para el file system
void *rfs_init(struct fuse_conn_info *conn) {
   return RFS_DATA; // se encarga de invocar el get_fuse_context
}

// Esta funcion se encarga de revisar los permisos de acceso a archivos
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_access(const char *path, int mask) {
   printf("--> Realizando el acces\n");
   int status = 0;
   char completePath[PATH_MAX];
   rfs_getcompletePath(completePath, path);
   status = access(completePath, mask);//se encarga de revisar los permisos
   if (status < 0) {
     printf("--> Error a la hora de realizar el access\n");
     status = -errno;
   }
   return status;
}

// Esta funcion se encarga de crear un archivo
// Si todo sale bien se retorna 0 de lo contrario da un error
int rfs_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
   printf("--> Realizando el create\n");
   int status = 0;
   char completePath[PATH_MAX];
   int fd;
   rfs_getcompletePath(completePath, path);
   fd = creat(completePath, mode);//se encarga de crear el archivo
   if (fd < 0) {
     printf("--> Error a la hora de realizar el create\n");
     status = -errno;
   }
   fi->fh = fd;
   return status;
}

// Esta estructura es la que se encarga de cambiar
//las funciones de FUSE por las reimplemtentadas por nosotros
struct fuse_operations rfs_operations = {
   .getattr = rfs_getattr,
   .mkdir = rfs_mkdir,
   .unlink = rfs_unlink,
   .rmdir = rfs_rmdir,
   .rename = rfs_rename,
   .utime = rfs_utime,
   .open = rfs_open,
   .read = rfs_read,
   .write = rfs_write,
   .statfs = rfs_statfs,
   .fsync = rfs_fsync,
   .opendir = rfs_opendir,
   .readdir = rfs_readdir,
   .init = rfs_init,
   .access = rfs_access,
   .create = rfs_create,
};
//Este es el main del fs
int main(int argc, char *argv[]) {
   struct rfs_struct *rfs_data;
   rfs_data = malloc(sizeof(struct rfs_struct));
   rfs_data->root = realpath("pruebaroot", NULL);
   return fuse_main(argc, argv, &rfs_operations, rfs_data);//esta es la llamada que se encarga de hacer que funcione
}
