%% Procesamiento de Señales - Laboratorio
%  Laboratorio 9
%Juan Gerardo Gonzalez Morales
%carne:17594
Fs = 250;         % Frecuencia de muestreo                    
Ts = 1/Fs;        % Período de muestreo
N = 500;          % Longitud de la señal (número de muestras)
t = (0:(N-1))*Ts; % Vector de tiempo

%% 1) Señales en tiempo
% Cree una señal, x1, que sea la suma de dos sinusoides. El primer sinusoide tiene una
% amplitud de A1 = 0.7 y una frecuencia f1 = 10 Hz. El segundo tiene una amplitud A2 = 1,
% y una frecuencia f2 = 100 Hz. Use el vector de tiempo creado arriba.
% Ayuda: A1*sin(2*pi*f1*t) devuelve un sinusoide de amplitud A1 y frecuencia f1.
% Cree también otra señal, x2, que sea x1 más ruido aleatorio entre -1 y 1 (usar rand).
% Cree una figura (figura 1) con dos subfiguras (una abajo de la otra). En la subfigura
% superior, graficar x1, y en la inferior, graficar x2. Graficar ambas versus el tiempo.
%datos
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








%% 2) Señales en dominio de frecuencia
% Aplique la fft a x1 y x2 (X1 y X2)
% En la figura 2, grafique la magnitud de X1/N en la subfigura superior, y la magnitud
% de X2/N en la subfigura inferior. Grafique ambas versus frecuencia, en el intervalo
% de 0 a 2*pi.
% Ayuda: pueden usar el script discretefourieranalysis.m como referencia.
% Usen plot en lugar de stem, para visualizar mejor las gráficas.
X1 = fft(x1);
Y = abs(X1/N);
X2 = fft(x2);
X = abs(X2/N);
k = 0:N-1;
w = (2*pi/N)*k;
%graficar
figure(2);clf;
subplot(2,1,1);
plot(w,Y);
title(' señal respecto frecuencia x1');
xlabel('frecuencia');
ylabel('señal x1');
subplot(2,1,2);
plot(w,X);
title('señal respecto frecuencia x2');
xlabel('frecuencia');
ylabel('señal x2');







% ¿Qué diferencias observa entre las dos gráficas?
%que en la primera graficar hay menos ruido provocado por la señal , en
%cambio en la segunda señal se puede observar fulctuaciones eevs a lo largo
%de la señal.
% ¿Cuáles son los valores máximos que observa en las gráficas?
%los valores maximos son de 0.5 de aplitud y minimos como 0.350
%¿Qué relación tienen estos valores con las amplitudes de los sinuosoides?
%la relacion es de un 60% de lo que nos llego realmente.




%% 3) Señales en dominio de frecuencia, fft con número extendido
% El algoritmo fft es más eficiente si el número de muestras corresponde a una potencia
% de dos. La función fft puede tomar como argumento un número para hacer calcular la DFT,
% que no necesariamente tiene que ser igual al número de muestras de la señal.
% Aplique la fft a x1 y x2, usando el número N2 definido a continuación (X1_2, X2_2).
% Note que N2 es la menor potencia de 2 mayor o igual al número de muestras de la señal.
% En la figura 3, grafique la magnitud de X1_2/N2 en la subfigura superior, y la magnitud
% de X2_2/N2 en la subfigura inferior. Grafique ambas versus frecuencia, en el intervalo
% de 0 a 2*pi.
%datos
N2 = 2^nextpow2(N);
t2 = (0:(N2-1))*Ts;
%señal
V1=Al*sin(2*pi*fl*t2);
V2=Al2*sin(2*pi*fl2*t2);
xD1=V1+V2;

xD2=xD1 + 2.*rand(size(t2))-1;

XD1 = fft(xD1);
X2_1 = abs(XD1/N2);
XD2 = fft(xD2);
X2_2 = abs(XD2/N2);
kD = 0:N2-1;
wD = (2*pi/N2)*kD;
%grafica
figure(3);clf;
subplot(2,1,1);
plot(wD,X2_1);
title(' señal respecto frecuencia X2_1');
xlabel('frecuancia');
ylabel('señal X1_1');
hold on;
subplot(2,1,2);
plot(wD,X2_2);
title(' señal respecto frecuencia X2_2');
xlabel('frecuencia');
ylabel('señal X2_2');

% ¿Qué diferencias observa respecto a las gráficas de la figura 2?
%en las 2 señales se puede observar que los picos no se comoportan tanto
%como lineas verticales , mas bien como curvas por lo que estan mas
%suavizadas y tienen un poco mas de area lograda por la curvatura.


%% 4) Gráficas en intervalo de -pi a pi
% En la figura 4, grafique la magnitud de X1_2/N2 en la subfigura superior, y la magnitud
% de X2_2/N2 en la subfigura inferior, pero versus frecuencia en el intervalo de -pi a pi.
k = -N2/2:N2/2-1;
wf = (2*pi/N2)*k;

figure(4);clf;
subplot(2,1,1);
plot(wf,X2_1);
title(' señal respecto frecuencia X2_1');
xlabel('frecuancia');
ylabel('señal X2_1');
hold on;
subplot(2,1,2);
plot(wf,X2_2);
title('señal respecto frecuencia X2_2');
xlabel('frecuencia');
ylabel('señal X2_2');

% ¿Qué puede decir respecto a la simetría del espectro de las señales?
% son casi la misma a excepcion del ruido del segundo grafico , su
% frecuencia sigue los mismo patrones, omo si la frecuencia fundamental
% fuera la misma.


%% 5) Aliasing
% Cree una señal, x3, que sea la suma de dos sinusoides, igual que antes. Pero esta vez,
% el primer sinusoide debe tener una frecuencia f3 = 240 Hz, con amplitud A3 = A1 = 0.7.
% El segundo sinusoide debe tener una frecuencia f4 = 150 Hz, con amplitud A4 = A2 = 1 Hz.
% Use el mismo vector de tiempo usado para x1 y x2.
% Aplique la fft a x3, usando el número N2 usado en la sección 3) (X3_2).
% En la figura 5, grafique la magnitud de X1_2/N2 en la subfigura superior, y la magnitud
% de X3_2/N2 en la subfigura inferior, versus frecuencia en el intervalo de -pi a pi.
%datos
Al3=0.7;
Al4=1;
f3=240;
f4=150;
%señal
V3=Al3*sin(2*pi*f3*t);
V4=Al4*sin(2*pi*f4*t);
x3=V3+V4;
X3 = fft(x3,N2);
X3_1 = abs(X3/N2);
wf = -N2/2:N2/2-1;
f3 = (2*pi/N2)*wf;
%graficar
figure(5);clf;
subplot(2,1,1);
plot(f3,X2_1);
title(' señal respecto frecuencia X2_1');
xlabel('frecuencia');
ylabel(' señal X2_1(t)');
hold on;
subplot(2,1,2);
plot(f3,X3_1);
title('señal respecto frecuencia X3_1');
xlabel('frecuencia');
ylabel(' señal X3_1');

% ¿Cómo se comparan las gráficas anteriores? Explique sus observaciones.
%las señales son demasiado similares, no le encuentro diferencias.