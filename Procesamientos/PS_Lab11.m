%% Procesamiento de Se�ales - Laboratorio
%  Laboratorio 11
%  ESCRIBA AQU� SUS DATOS 
%juan Gerardo Gonzalez MOrales
%carne 17594
%seccion 10

%% Primera Parte
% Cargue los datos del archivo PS_Lab11_datos.mat. Ver� tres se�ales, x1, x2 y x3, la
% frecuencia de muestreo usada, y un vector de tiempo.
% Investigue las funciones sound y soundsc en el help de Matlab. �selas para reproducir
% las se�ales x1, x2 y x3.
% NOTA: antes de subir su script a Canvas, comente las l�neas con los llamados a las
% funciones sound y soundsc.
%llamando a x1 a x2 y x3
load('PS_Lab11_datos.mat','x1');
load('PS_Lab11_datos.mat','x2');
load('PS_Lab11_datos.mat','x3');
%sound de x1 , x2 , x3
%sound(x1);
%sound(x2);
%sound(x3);
%soundsc de x1 , x2 x3.
%soundsc(x1);
%soundsc(x2);
%soundsc(x3);

% 1.1) �Nota alguna diferencia entre usar sound y soundsc para alguna de las se�ales? De
%      ser as�, �cu�l cree que sea la raz�n?
% RESPUESTA:
%las primeras 2 se�ales se escuchan iguales a excepcion de la tercera, que
%la se�al del sonido con la funcion sound se escucha un poco difuminada, en
%cambio misma se�al con soundsc se escucha mas suave , mas fina.


% 1.2) Seg�n lo que escuch�, �cree que hay alguna relaci�n entre x3 y las otras dos
%      se�ales? 

% RESPUESTA:
%segun lo que escuche esque el tiempo es el mismo, y por alguna razon la
%primera y la tercera son muy similares. ademas de que solo se escuha un
%sonido que las caracteriza.Como s tuvieran un solo tono de sonido.


% Obtenga el espectro de amplitud unilateral de x1, x2 y x3. Grafique los tres como
% subfiguras en la figura 1 (subfigura superior para x1, central para x2, inferior para
% x3). El eje horizontal de cada gr�fica debe ser de frecuencia, en Hz. NO use la
% siguiente potencia de 2 para calcular la fft. Note que las se�ales ya tienen un n�mero
% de muestras que coinciden con una potencia de 2.
%se�al unitaria de x1
X1 = fft(x1);
Lar1= length(x1);
f1 = Fs*(0:(Lar1/2))/Lar1;
P2 = abs(X1/Lar1);
P1 = P2(1:Lar1/2+1);
P1(2:end-1) = 2*P1(2:end-1);
%se�al unitaria de x2
X2 = fft(x2);
Lar2= length(x2);
f2 = Fs*(0:(Lar2/2))/Lar2;
P4 = abs(X2/Lar2);
P3 = P4(1:Lar2/2+1);
P3(2:end-1) = 2*P3(2:end-1);
%se�al unitaria de x3
X3 = fft(x1);
Lar3= length(x3);
f3 = Fs*(0:(Lar3/2))/Lar3;
P6 = abs(X3/Lar3);
P5 = P6(1:Lar3/2+1);
P5(2:end-1) = 2*P5(2:end-1);
figure(1);clf;
subplot(2,2,1);
plot(f1,P1);
title(' se�al respecto frecuencia');
xlabel('frecuencia');
ylabel('se�al x1');
subplot(2,2,2);
plot(f2,P3);
title(' se�al respecto frecuencia');
xlabel('frecuencia Hz');
ylabel('se�al x2');
subplot(2,2,3);
plot(f3,P5);
title(' se�al respecto frecuencia');
xlabel('frecuencia Hz');
ylabel('se�al x3');







% 1.3) Seg�n lo que observ�, �qu� tipo de se�ales cree que son x1 y x2? �C�mo cree que se
%      generaron?
% RESPUESTA:
%creoq eue se generaron desde algun tipo  de frecuencia  de audio como de
%algun dispositivo de creacion de frecuencias agudas y graves.

% 1.4) Seg�n lo que observ�, �cree que hay alguna relaci�n entre x3 y las otras dos
%      se�ales? �Coincide con lo que contest� en la pregunta 1.2)? Explique.
% RESPUESTA:
% si ya que tienen el mismo espectro de frecienca x3 y x1 son bastantes
% similares el pico de frecuencia se enuentra en el mismo lugar.

%% Segunda Parte
% Use la funci�n freqz para obtener vectores con la respuesta en frecuencia y la
% frecuencia angular para los sistemas H1 y H2 descritos en la gu�a.
% En la figura 2, grafique la magnitud (NO en dB) de la respuesta versus la
% frecuencia en Hz (NO en rad/muestra). Ayuda: necesita usar la frecuencia de muestreo Fs.
% En la subfigura superior grafique la magnitud correspondiente a H1, y en la subfigura
% inferior grafique la magnitud correspondiente a H2. Active la cuadr�cula para las
% gr�ficas.

%funcion 1

num1 = [0.2];
den1 = [1 -0.8];

[h1,fase1]=freqz(num1,den1,8192,Fs);
%funcion 2
num2 = [0.5 -0.5];
den2 = [1 -0.5];


[h2,fase2]=freqz(num2,den2,8192,Fs);


figure(2);
clf;
subplot(2, 1, 1)
plot(fase1,abs(h1));
title ("H1")
xlabel("Frecuencia en Hz")
ylabel("Magnitud")
subplot(2, 1, 2)
plot(fase2,abs(h2));
title ("H2")
xlabel("Frecuencia en Hz")
ylabel("Magnitud")







% 2.1) �Qu� tipo de filtros son H1 y H2?
% 1 filtro pasabajas
% 2 filtro pasa altas
% RESPUESTA:


%% Tercera parte
% Obtenga variables tipo tf discreto para H1 y H2. Recuerde usar el par�metro de per�odo
% de muestreo. Use las variables para obtener las respuestas de H1 y H2 a la se�al de
% entrada x3. Llame a las respuestas y3H1 y y3H2. Ayuda: Hicieron algo similar en el lab7.



% Use la funci�n soundsc para escuchar las respuestas obtenidas con H1 y H2.
% NOTA: antes de subir su script a Canvas, comente las l�neas con los llamados a la
% funci�n soundsc.

num1 = [0.2];
den1 = [1 -0.8];

num2 = [0.5 -0.5];
den2 = [1 -0.5];
H1 = tf(num1,den1)
H2 = tf(num2,den2)



Y3h1 = lsim(H1,x3,t);
Y3h2 = lsim(H2,x3,t);
%sonidos de Y3h1 y Y3h2
soundsc(Y3h1);
soundsc(Y3h2);

% 3.1) Describa lo que escuch�. �Qu� le hizo H1 a x3? �Qu� le hizo H2 a x3?
% RESPUESTA:



% Obtenga el espectro de amplitud unilateral de y3H1 y y3H2. Grafique los dos como
% subfiguras en la figura 3 (subfigura superior para y3H1, e inferior para y3H2.
% El eje horizontal de cada gr�fica debe ser de frecuencia, en Hz. NO use la
% siguiente potencia de 2 para calcular la fft.
%se�al de Y3h1
X4 = fft(Y3h1);
Lar4= length(X4);
f4 = Fs*(0:(Lar4/2))/Lar4;
P8 = abs(X4/Lar4);
P7 = P8(1:Lar4/2+1);
P7(2:end-1) = 2*P7(2:end-1);
%se�al de Y3h2
X5 = fft(Y3h2);
Lar5= length(X5);
f5 = Fs*(0:(Lar5/2))/Lar5;
P10 = abs(X5/Lar5);
P9 = P10(1:Lar5/2+1);
P9(2:end-1) = 2*P9(2:end-1);
figure(3);clf;
subplot(2,1,1);
plot(f4,P7);
title(' se�al respecto frecuencia');
xlabel('frecuencia Hz');
ylabel('se�al Y3h1');
subplot(2,1,2);
plot(f5,P9);
title(' se�al respecto frecuencia');
xlabel('frecuencia Hz');
ylabel('se�al Y3h2');

% 3.2) Describa lo que observa en los espectros. �Qu� pas� con los picos, compar�ndolos
%      con lo observado en la Primera Parte? �Qu� le hizo H1 a x3? �Qu� le hizo H2 a x3?
% RESPUESTA:
% pareciera como si la conviertiera en x1 y x2 del ejercicio 1, se oyen
% similar , y las graficas son bastantes parecidas .Es como si x3 fuera la
% se�al que tratan de armonizar.


% 3.3) Compare con atenci�n las figuras 2 y 3. Discuta brevemente si lo escuchado y
%      observado en las gr�ficas tiene sentido y es consistente.
% RESPUESTA:
%si tiene sentido ya que las grafica 1 solo tiene un pico de frecuencia, al
%igual que la fgura 2 solo muestra 2 picos altos de frecuencias la cual al
%escucharla se oyen 2 sonidos caraterristicos.
