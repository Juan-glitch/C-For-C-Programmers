import fitz  # PyMuPDF

def pdf_to_png(pdf_path, output_folder):
    # Abre el archivo PDF
    pdf_document = fitz.open(pdf_path)
    
    # Itera a través de cada página
    for page_num in range(len(pdf_document)):
        # Obtiene la página
        page = pdf_document.load_page(page_num)
        
        # Renderiza la página a una imagen
        pix = page.get_pixmap()
        
        # Guarda la imagen como PNG
        output_path = f"{output_folder}/page_{page_num + 1}.png"
        pix.save(output_path)
    
    print(f"El PDF ha sido convertido a imágenes PNG y guardado en {output_folder}")

# Ejemplo de uso
pdf_path = "/app/resources/kk_ejemplo.pdf"  # Reemplaza con la ruta de tu archivo PDF
output_folder = "./"  # Reemplaza con la carpeta donde deseas guardar las imágenes

pdf_to_png(pdf_path, output_folder)
