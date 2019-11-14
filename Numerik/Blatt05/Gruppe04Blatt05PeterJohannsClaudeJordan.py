# Numerik Gruppe 04 Peter Johann, Claude Jordan Blatt 5 Nummer 2
"""zu b):
-Stoff wird besser komprimiert als stoff2, da seine 'Linien'
gerade verlaufen
-bei Lena existiert kein 'Muster', was einfach wiederholt werden
kann, bei den anderen beiden schon
-bei p = 1 gibt es in U nur einen Vektor und in V ebenfalls, außerdem nur einen
zugehörigen Singulärwert, der der größte ist, also der wichtigste"""



import numpy as np
from PIL import Image
from matplotlib import cm, pyplot


def Compress(Image, ComponentCount):
    """This function uses a singular value decomposition to compress an image.
      \param Image An quadratic array providing the image. Entries provide the 
             brightness of indidividual pixels, rows correspond to scanlines.
      \param ComponentCount The number of singular values to be maintained in the 
             compressed representation.
      \return A tuple (U,SingularValues,V,CompressionRatio) such that U*Sigma*V^* 
              provides an approximation to the original image when Sigma is a 
              diagonal matrix with SingularValues on its main diagonal. 
              CompressionRatio should provide the quotient of the number of scalars 
              in Image and the number of scalars in the returned representation of 
              Image."""
    u, s, vh = np.linalg.svd(Image)
    prev = len(s)
    u = u[:, 0:ComponentCount]
    s = s[0:ComponentCount]
    vh = vh.transpose()
    vh = vh.conjugate()
    vh = vh[:, 0:ComponentCount]
    compression_scale = prev / len(s)
    return u, s, vh, compression_scale


def Decompress(U, SingularValues, V):
    """Given a compressed representation of an image as produced by Compress() this 
       function reconstructs the original image approximately and returns it."""
    Sigma = np.diag(SingularValues)
    VH = V.transpose().conjugate()
    return U @ Sigma @ VH


if __name__ == "__main__":
    # Define the task
    ImageFileNameList = ["Lena", "Stoff", "Stoff2"];
    ComponentCountList = [1, 4, 8, 32, 64];
    # Iterate over all tasks and generate one large plot
    PlotIndex = 1;
    for ImageFileName in ImageFileNameList:
        ImagePath = ImageFileName + ".png";
        img = Image.open(ImagePath);
        # Convert to numpy array
        imgmat = np.array(list(img.getdata(band=0)), float)
        # Reshape according to orginal image dimensions
        imgmat.shape = (img.size[1], img.size[0])
        imgmat = np.matrix(imgmat)
        for ComponentCount in ComponentCountList:
            # Define a subplot for this decompressed image
            Axes = pyplot.subplot(len(ImageFileNameList), len(ComponentCountList), PlotIndex);
            Axes.set_xticks([]);
            Axes.set_yticks([]);
            Axes.set_title(ImageFileName + ", p=" + str(ComponentCount));
            PlotIndex += 1;
            # Apply compression
            U, SingularValues, V, CompressionRatio = Compress(imgmat, ComponentCount);
            # Apply decompression and show the result
            DecompressedImage = Decompress(U, SingularValues, V);
            pyplot.imshow(DecompressedImage, cmap=cm.gray);
            # Compute and print the compression ratio
            print("Compression ratio for p=" + str(ComponentCount) + " is " + str(CompressionRatio) + ":1.");
        print("");
    pyplot.show();
