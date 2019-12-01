![OCR](https://projet-ocr-epita.web-edu.fr/images/logo.jpg)
# A super cool Optical Character Recognition System.

**HELE** (for _SaraH-PierrE-PauL-NepheliE_) is a groupe formed at the school EPITA so as to work on a project.
An [optical character recognition system](https://searchcontentmanagement.techtarget.com/definition/OCR-optical-character-recognition) is developed as part of the EPITA second year project. It is powered by artificial intelligence with a [neural network](http://neuralnetworksanddeeplearning.com/index.html) which is able to learn a tones of different character such as Unicode table.

This software is capable of extracting a text from an image with a photo by segmenting the image. It segments the page in the different letters, and return the character expected with the neural network.

## REQUIREMENTS

The HELE's OCR requires the following C librairies to work:

- [SDL](https://www.libsdl.org/ "SDL")
- [GTK+](https://www.gtk.org/ "GTK+")

## INSTALLATION
Before installing, make sure that you fill all the requirements. Please refer to _Requirements_ section.

<ul>
	<li> Download the archive from <a href="https://github.com/Lyrianna/OCR">GitHub</a></li>
	<li> Unzip the archive (Using  <a href="https://www.7-zip.org/">7-ZIP</a> or <a href="http://www.winzip.com/">Winzip</a> for example).</li>
	<li> When you are in ??? repository, open a Terminal and execute the following commands:</li>
	<pre><code>$ make<br><code>

</ul>

## HOW IT WORKS ?

The OCR is processing as follow:

- Loading the image
- Deleting the colors (grayscale, black and white)
- Pretreatment
- Detection of text blocks
- Character detection
- Recognition of detected characters
- Reconstruction of the text

The division of blocks of text into characters is necessary to send them to the neural network.

Character recognition is the central part of OCR, it requires a learning phase during which the neural network will learn to recognize the different characters.

To launch it, please refer to section _Installation_.

Code programmation de notre OCR pour notre projet de S3 dans l'école EPITA.

## CREDITS
Students of Epita at the origin of the code : <tt>Unikarah</tt>, <tt>Lyrianna</tt>, <tt>Pierre</tt> and <tt>Paul</tt>.

Please take the time to see our website [projetocr](https://projet-ocr-epita.web-edu.fr/).

