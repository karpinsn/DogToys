width = 1024;
height = 768;

x = linspace(0.0, 1.0, width);
fringeImage = zeros(height, width, 3);

% Frequency of the fringe
frequency = 4.0;
angularFrequency = 2.0 * pi * frequency;

fringeImage(:,:,1) = ones(height, 1) * (1.0 - cos(angularFrequency * x - (2 * pi / 3))) * .5;
fringeImage(:,:,2) = ones(height, 1) * (1.0 - cos(angularFrequency * x)) * .5;
fringeImage(:,:,3) = ones(height, 1) * (1.0 - cos(angularFrequency * x + (2 * pi / 3))) * .5;

fringeImage = fringeImage * 255.0;
fringeImage = uint8(fringeImage);
imwrite(fringeImage, 'fringe.png');