%616
P = 2001;
Q = 2001;

f = fopen('dibujo.raw', 'r');
M = fread(f, 'float');
M = reshape(M, Q, P);
fclose(f);
figure(1)
imagesc(M)
colormap( [jet(); flipud( jet() ); 0 0 0] );

f = fopen('dibujo-mio.raw', 'r');
M = fread(f, 'float');
M = reshape(M, P, Q);
fclose(f);
figure(2)
imagesc(M)
colormap( [jet(); flipud( jet() ); 0 0 0] );