import os
from PyPDF2 import PdfReader, PdfWriter

def split_pdf(file, directory, ranges):
    pdf = PdfReader(file)
    for i, page_range in enumerate(ranges):
        pdf_writer = PdfWriter()
        for page in range(page_range[0], page_range[1]):
            pdf_writer.add_page(pdf.pages[page])

        output_filename = os.path.join(directory, '{}_part_{}.pdf'.format(
            os.path.splitext(os.path.basename(file))[0], i+1))

        with open(output_filename, 'wb') as out:
            pdf_writer.write(out)

        print('Created: {}'.format(output_filename))

# Define the page ranges for each part
# ranges = [(0, 376), (376, 606), (606, 788), (788, 1162)]
# ranges = [(0, 162), (162, 334), (334, 525)]
ranges = [(0, 410), (410, 727)]
split_pdf('FilesForProcessing/a.pdf', 'FilesAfterProcessing', ranges)