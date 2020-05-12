%% Procesamiento de Señales - Laboratorio
%  Laboratorio 10
%Juan Gonzalez 
%17594
Fs = 250;         % Frecuencia de muestreo                    
Ts = 1/Fs;        % Período de muestreo
N = 500;          % Longitud de la señal (número de muestras)
t = (0:(N-1))*Ts; % Vector de tiempo
%% 1) Ajuste del espectro de frecuencia usando fftshift
% Cree las mismas señales en tiempo que en el laboratorio 9:
% x1 es la suma de dos sinusoides con amplitudes y frecuencias A1 = 0.7, f1 = 10 Hz,
% A2 = 1 y f2 = 100 Hz.
% x2 es igual a x1 más ruido aleatorio entre -1 y 1 (usar rand).
% Use la frecuencia de muestreo, el número de muestras y el vector de tiempo definidos en
% el script de la Tercera Parte del lab 9.
Al=0.7;
fl = 10;         % Frecuencia de muestreo  

Al2=1;
fl2 = 100;
%señales
V1=Al*sin(2*pi*fl*t);
V2=Al2*sin(2*pi*fl2*t);
x1=V1+V2;

x2=x1 + 2.*rand(size(t))-1;
%graficar
figure(1);clf;
subplot(2,1,1);
plot(t,x1);
title(' Sin ruido');
xlabel('t');
ylabel('señal x1');
subplot(2,1,2);
plot(t,x2);
title('Con ruido');
xlabel('tiempo');
ylabel('señal x2');




% Aplique la fft a x1 y x2 (X1, X2). No necesita usar la siguiente potencia de 2.
% Investigue la función fftshift y úsela para reordenar X1 y X2 tal que el componente de
% frecuencia cero esté al centro del array. Grafique los espectros reordenados USANDO
% LA FUNCIÓN STEM. Las gráficas deben mostrarse como subfiguras superior e inferior en la
% figura 1. El eje horizontal de cada gráfica debe ser de frecuencia, en Hz, no en
% radianes por muestra (como se hizo en el lab 9).
% Ayuda: el vector con las frecuencias que debe usar para el eje horizontal de las figuras
% debe estar en el intervalo [-Fs/2, Fs/2), que corresponde a las frecuencias discretas en
% el intervalo [-pi, pi).

X1 = fft(x1);
Y = fftshift(X1);
X2 = fft(x2);
X = fftshift(X2);
k = (-N/2:N/2-1)*(Fs/N);
powershift = abs(Y).^2/N;     % zero-centered power
powershift2 = abs(X).^2/N;     % zero-centered power
w = (2*pi/N)*k;
%graficar
figure(2);clf;
subplot(2,1,1);
stem(k,powershift);
title(' señal respecto frecuencia x1');
xlabel('frecuencia');
ylabel('señal x1');
subplot(2,1,2);
stem(k,powershift2);
title('señal respecto frecuencia x2');
xlabel('frecuencia');
ylabel('señal x2');


% ¿Según sus gráficas, en qué frecuencias aparecen los picos del espectro (los máximos)?
%en -100 y 100 


% ¿Cuánto son los valores máximos observados? ¿Qué relación tienen con las amplitudes A1 y
% A2 de los sinusoides? los valores observados del A1 maximos son menores a
% A2 ya que la amplitud de la señor A2 tiene mayores picos. 


%% 2) Espectro de amplitud unilateral
% Siga las indicaciones del help de la función fft para obtener y graficar el espectro
% de amplitud unilateral (single-sided amplitude spectrum) de x1 y x2. USE LA FUNCIÓN
% STEM. Las gráficas deben mostrarse como subfiguras en la figura 2. El eje horizontal de
% cada gráfica debe ser de frecuencia, en Hz. No necesita usar la siguiente potencia de 2
% para calcular la fft.
Y1 = fft(x1);
P2 = abs(Y1/N);
P1 = P2(1:N/2+1);
P1(2:end-1) = 2*P1(2:end-1);
X1 = fft(x2);
P4 = abs(X1/N);
P3 = P4(1:N/2+1);
P3(2:end-1) = 2*P3(2:end-1);
f = Fs*(0:(N/2))/N;
figure(3);clf;
subplot(2,1,1);
stem(f,P1);
title(' señal respecto frecuencia x1');
xlabel('frecuencia');
ylabel('señal x1');
subplot(2,1,2);
stem(f,P3);
title('señal respecto frecuencia x2');
xlabel('frecuencia');
ylabel('señal x2');

% ¿Cuál es el rango de frecuencias del eje horizontal?
% de 0 a 140


% ¿Según sus gráficas, en qué frecuencias aparecen los picos del espectro?
%en 10 y 100

% ¿Cuánto son los valores máximos observados? ¿Qué relación tienen con las amplitudes A1 y
% A2 de los sinusoides?
% A1 en 0.70 y la mayor 1 y en A2 la menor 0.72 y la mayor 1 , lo cual tene
% concordancia con los datos de A1 y A2 ya que sus pcos se encuentra a 1 a
% 0.70 a 1 


%% 3) Tranformada inversa
% Cargue las variable X3 y Fs3 almacenadas en el archivo PS_Lab10_datos.mat. X3
% corresponde a la transformada discreta de fourier de cierta señal x3, la cual fue
% muestreada con una frecuencia de muestreo de 1000 Hz.
% Grafique el espectro de amplitud unilateral de x3 en la figura 3. Como en la sección 2,
% grafique versus frecuencia, en Hz.

load('PS_Lab10_datos.mat','X3');
load('PS_Lab10_datos.mat','Fs3');
Lar3= length(X3);
f2 = Fs3*(0:(Lar3/2))/Lar3;
P6 = abs(X3/Lar3);
P5 = P6(1:Lar3/2+1);
P5(2:end-1) = 2*P5(2:end-1);
figure(4);clf;

plot(f2,P5);
title(' señal respecto frecuencia');
xlabel('frecuencia');
ylabel('señal');

% Según el espectro, ¿qué componentes de frecuencia son los predominantes? Asumiendo que
% la señal original en tiempo x3 fuese una combinación de sinusoides, ¿Qué amplitudes 
% tendrían dichos sinusoides?
% tendrian los mismo picos de amplitud

% Investigue la función ifft en el help de Matlab. Use la ifft para obtener x3.
% En la subfigura superior de la figura 4, grafique el resultado de la ifft versus tiempo
% discreto (de 0 al número de muestras de x3 menos 1).
% En la subfigura inferior de la figura 4, grafique el resultado de la ifft versus tiempo,
% en segundos.

x3=ifft(X3);
ts3 = 1/Fs3;
t3=0:Lar3-1;
Lar4= length(x3);
f3 = Fs3*(0:(Lar3/2))/Lar3;
P8 = abs(x3/Lar3);
f2 = Fs3*(0:(Lar3/2))/Lar3;

P7 = P8(1:Lar3/2+1);
P7(2:end-1) = 2*P7(2:end-1);



figure(5);clf;
subplot(2,1,1);
plot(t3,x3);
title(' señal respecto frecuencia x3');
xlabel('tiempo');
ylabel('amplitud');
subplot(2,1,2);
plot(f2,P7);
title(' señal respecto frecuencia x3');
xlabel('tiempo');
ylabel('amplitud');


% ¿Tienen sentido las gráficas de x3 observadas en la figura 4? Explique brevemente.
% si ya que tienen las misma amplitud

%% 4) Respuesta en frecuencia de sistemas LTI
% Use la función freqz, mostrada en la lección de teoría #9, para obtener vectores con la
% respuesta en frecuencia y la frecuencia angular para el sistema H1 descrito en la guía.
% Ayuda: llame a la función así: [h,w] = freqz(b,a); Nota: podría agregar un
% tercer argumento en la función freqz, con el número de puntos deseados. Si no se
% incluye, la función usa un número por defecto.
% En la figura 5, grafique la magnitud (NO en dB) de la respuesta versus la frecuencia
% angular en la subfigura superior, y la fase (en grados) de la respuesta versus la
% frecuencia angular en la subfigura inferior. Active la cuadrícula para las gráficas.
% Ayuda: para verificar que sus gráficas son correctas, puede usar la función fvtool.
% NO INCLUYA EL LLAMADO A fvtool EN SU SCRIPT FINAL QUE SUBIRÁ A CANVAS.


%funcion 1
tiempo3 =1e-3;
num1 = [0.1];
den1 = [1 -0.9];
H1 = tf(num1, den1, tiempo3);
[h1,fase1]=freqz(num1,den1);
ang1=angle(h1)*180/pi;

figure(6);
clf;
subplot(2, 1, 1)
plot(fase1/pi,abs(h1));
title ("H1")
xlabel("Frecuencia ángular")
ylabel("Amplitud dB")

subplot(2, 1, 2)
plot(fase1/pi,ang1);
xlabel("Frecuencia ángular")
ylabel("Fase en grados")

% Repita lo anterior para el sistema H2. Grafique la magnitud y fase de la respuesta en
% frecuencia en la figura 6.

%funcion 2
num2 = [0.9 -0.9];
den2 = [1 -0.9];


[h2,fase2]=freqz(num2,den2);
ang2=angle(h2)*180/pi;

figure(7);
clf;
subplot(2, 1, 1)
plot(fase2/pi,abs(h2));
title ("H2")
xlabel("Frecuencia en angulo")
ylabel("Amplitud DB")
subplot(2, 1, 2)
plot(fase2/pi,ang2);
xlabel("Frecuencia en angulo")
ylabel("graodos")

% Repita lo anterior para el sistema H3. Grafique la magnitud (ESTA VEZ EN dB), y fase de
% la respuesta en frecuencia en la figura 7.

%Funcion 3
num3 = [10^-3 10^-3];
den3 = [2 -2];


[h3,fase3]=freqz(num3,den3);
ang3=angle(h3)*180/pi;

figure(8);
clf;
subplot(2, 1, 1)
plot(fase3/pi,20*log10(abs(h3)));
title ("H3")
xlabel("Frecuencia en angulo")
ylabel("Amplitud dB")
subplot(2, 1, 2)
plot(fase3/pi,ang3);
xlabel("Frecuencia en angulo")
ylabel("grados")





