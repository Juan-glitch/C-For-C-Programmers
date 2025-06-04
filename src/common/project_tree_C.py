#!/usr/bin/env python3
"""
Version: 0.0.2 | Updated: 2025-03-22 | Branch: DEV | Commit: c6cc354
Generador de estructura de directorios para documentacion en proyectos C/C++.

Este script genera un árbol de directorios en formato ASCII, ideal para incluir
en la documentación de proyectos (por ejemplo, en el README.md). Se enfoca en mostrar
únicamente archivos con extensiones típicas de C y C++.

Uso:
    python project_tree.py [--output README.md] [--ignore-dirs .git,venv] [--ignore-files *.pyc,*.tmp]
                              [--extensions .c,.cpp,.cc,.h,.hpp]

Ejemplos:
    1. Mostrar árbol en consola:
       python project_tree.py

    2. Guardar en README.md e ignorar archivos .log y .tmp:
       python project_tree.py --output README.md --ignore-files "*.log,*.tmp"

    3. Ignorar directorios específicos y especificar extensiones:
       python project_tree.py --ignore-dirs ".git,venv,temp" --extensions ".c,.cpp,.h"
"""

import os
import argparse
import fnmatch

def generate_project_tree(start_path, ignore_dirs=[], ignore_files=[], allowed_extensions=None, output_file=None):
    """
    Description:
        generate_project_tree function. Genera un árbol de directorios en formato ASCII para un proyecto C/C++.
    Args:
        start_path: Ruta inicial desde la que se generará el árbol.
        ignore_dirs: Lista de directorios a ignorar (por nombre).
        ignore_files: Lista de patrones de archivos a ignorar.
        allowed_extensions: Lista de extensiones de archivo que se incluirán.
        output_file: Nombre del archivo en el que se guardará la salida (opcional).
    Returns:
        None
    """
    # Inicio del árbol en formato ASCII
    tree = ['```\n']

    def should_ignore(name, is_dir):
        """
        Description:
            should_ignore function. Verifica si un archivo o directorio debe ser ignorado.
        Args:
            name: Nombre del archivo o directorio.
            is_dir: Booleano que indica si es un directorio.
        Returns:
            True si debe ignorarse, False en caso contrario.
        """
        if is_dir:
            return name in ignore_dirs
        else:
            return any(fnmatch.fnmatch(name, pattern) for pattern in ignore_files)

    def build_tree(path, prefix='', is_last=True):
        """
        Description:
            build_tree function. Construye recursivamente la estructura del árbol.
        Args:
            path: Ruta actual del directorio o archivo.
            prefix: Prefijo para formatear las líneas del árbol.
            is_last: Booleano que indica si es el último elemento en el nivel actual.
        Returns:
            None
        """
        # Nombre del archivo o directorio
        name = os.path.basename(path)
        # Formato del árbol (último elemento o no)
        line = f'{prefix}└── {name}' if is_last else f'{prefix}├── {name}'
        if prefix == '':
            tree.append(f'{name}\n')
        else:
            tree.append(f'{line}\n')

        # Si es un directorio, procesar su contenido
        if os.path.isdir(path):
            new_prefix = prefix + ('    ' if is_last else '│   ')
            try:
                # Obtener elementos del directorio y filtrar ignorados
                items = sorted(os.listdir(path))
                items = [item for item in items if not should_ignore(item, os.path.isdir(os.path.join(path, item)))]
            except PermissionError:
                # Saltar directorios sin permisos de lectura
                return

            # Separar directorios y archivos
            dirs = [d for d in items if os.path.isdir(os.path.join(path, d))]
            files = [f for f in items if not os.path.isdir(os.path.join(path, f))]
            # Filtrar archivos según las extensiones permitidas
            if allowed_extensions:
                files = [f for f in files if os.path.splitext(f)[1].lower() in allowed_extensions]
            # Ordenar y procesar los elementos
            sorted_items = dirs + files
            for index, item in enumerate(sorted_items):
                is_last_item = (index == len(sorted_items) - 1)
                build_tree(os.path.join(path, item), new_prefix, is_last_item)

    # Construcción del árbol
    build_tree(start_path)
    tree.append('```')
    result = ''.join(tree)

    # Guardar en archivo o imprimir en consola
    if output_file:
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(f'## Estructura del proyecto\n\n{result}\n')
        print(f'✓ Árbol generado en {output_file}')
    else:
        print(result)

if __name__ == '__main__':
    # Valores predeterminados para ignorar directorios y archivos
    DEFAULT_IGNORE_DIRS = ['.git', '__pycache__', 'venv', '.pytest_cache']
    DEFAULT_IGNORE_FILES = ['*.pyc', '*.tmp', '*.log']
    DEFAULT_EXTENSIONS = ['.c', '.cpp', '.cc', '.h', '.hpp']

    # Configuración de argumentos del script
    parser = argparse.ArgumentParser(
        description='Genera un árbol de directorios en formato ASCII para la documentación de proyectos en C/C++.',
        epilog='Ejemplo: python project_tree.py --output README.md --ignore-dirs .git,venv --extensions .c,.cpp,.h'
    )
    parser.add_argument('--output', help='Archivo de salida (ej. README.md)', default=None)
    parser.add_argument('--ignore-dirs', help='Directorios a ignorar (separados por comas)', default=','.join(DEFAULT_IGNORE_DIRS))
    parser.add_argument('--ignore-files', help='Patrones de archivos a ignorar (separados por comas, soporta wildcards)', default=','.join(DEFAULT_IGNORE_FILES))
    parser.add_argument('--extensions', help='Extensiones de archivo a incluir (separadas por comas)', default=','.join(DEFAULT_EXTENSIONS))
    
    # Parseo de argumentos
    args = parser.parse_args()
    ignore_dirs = [item.strip() for item in args.ignore_dirs.split(',')]
    ignore_files = [item.strip() for item in args.ignore_files.split(',')]
    allowed_extensions = [ext.strip().lower() for ext in args.extensions.split(',')]

    # Generación del árbol de directorios
    generate_project_tree(start_path=os.getcwd(),
                          ignore_dirs=ignore_dirs,
                          ignore_files=ignore_files,
                          allowed_extensions=allowed_extensions,
                          output_file=args.output)
