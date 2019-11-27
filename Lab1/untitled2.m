length = 256;

f = fopen('test/circulos.raw', 'r');
s = fread(f, 'int'); 
fclose(f);
s = reshape(s, length, length);
s = s';

figure(1);
imagesc(s); 
axis('square'); 
colormap(gray); 

f = fopen('outSIMD.raw', 'r');
s = fread(f, 'int'); 
fclose(f);
s = reshape(s, length, length);
s = s';

figure(3);
imagesc(s); 
axis('square'); 
colormap(gray); 

f = fopen('outSeq.raw', 'r');
s = fread(f, 'int'); 
fclose(f);
s = reshape(s, length, length);
s = s';

figure(2);
imagesc(s); 
axis('square'); 
colormap(gray); 

