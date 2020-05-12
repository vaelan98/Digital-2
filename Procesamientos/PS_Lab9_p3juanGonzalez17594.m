%% Procesamiento de Se�ales - Laboratorio
%  Laboratorio 9
%Juan Gerardo Gonzalez Morales
%carne:17594
Fs = 250;         % Frecuencia de muestreo                    
Ts = 1/Fs;        % Per�odo de muestreo
N = 500;          % Longitud de la se�al (n�mero de muestras)
t = (0:(N-1))*Ts; % Vector de tiempo

%% 1) Se�ales en tiempo
% Cree una se�al, x1, que sea la suma de dos sinusoides. El primer sinusoide tiene una
% amplitud de A1 = 0.7 y una frecuencia f1 = 10 Hz. El segundo tiene una amplitud A2 = 1,
% y una frecuencia f2 = 100 Hz. Use el vector de tiempo creado arriba.
% Ayuda: A1*sin(2*pi*f1*t) devuelve un sinusoide de amplitud A1 y frecuencia f1.
% Cree tambi�n otra se�al, x2, que sea x1 m�s ruido aleatorio entre -1 y 1 (usar rand).
% Cree una figura (figura 1) con dos subfiguras (una abajo de la otra). En la subfigura
% superior, graficar x1, y en la inferior, graficar x2. Graficar ambas versus el tiempo.
%datos
Al=0.7;
fl = 10;         % Frecuencia de muestreo  

Al2=1;
fl2 = 100;
%se�ales
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
ylabel('se�al x1');
subplot(2,1,2);
plot(t,x2);
title('Con ruido');
xlabel('tiempo');
ylabel('se�al x2');








%% 2) Se�ales en dominio de frecuencia
% Aplique la fft a x1 y x2 (X1 y X2)
% En la figura 2, grafique la magnitud de X1/N en la subfigura superior, y la magnitud
% de X2/N en la subfigura inferior. Grafique ambas versus frecuencia, en el intervalo
% de 0 a 2*pi.
% Ayuda: pueden usar el script discretefourieranalysis.m como referencia.
% Usen plot en lugar de stem, para visualizar mejor las gr�ficas.
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
title(' se�al respecto frecuencia x1');
xlabel('frecuencia');
ylabel('se�al x1');
subplot(2,1,2);
plot(w,X);
title('se�al respecto frecuencia x2');
xlabel('frecuencia');
ylabel('se�al x2');







% �Qu� diferencias observa entre las dos gr�ficas?
%que en la primera graficar hay menos ruido provocado por la se�al , en
%cambio en la segunda se�al se puede observar fulctuaciones eevs a lo largo
%de la se�al.
% �Cu�les son los valores m�ximos que observa en las gr�ficas?
%los valores maximos son de 0.5 de aplitud y minimos como 0.350
%�Qu� relaci�n tienen estos valores con las amplitudes de los sinuosoides?
%la relacion es de un 60% de lo que nos llego realmente.




%% 3) Se�ales en dominio de frecuencia, fft con n�mero extendido
% El algoritmo fft es m�s eficiente si el n�mero de muestras corresponde a una potencia
% de dos. La funci�n fft puede tomar como argumento un n�mero para hacer calcular la DFT,
% que no necesariamente tiene que ser igual al n�mero de muestras de la se�al.
% Aplique la fft a x1 y x2, usando el n�mero N2 definido a continuaci�n (X1_2, X2_2).
% Note que N2 es la menor potencia de 2 mayor o igual al n�mero de muestras de la se�al.
% En la figura 3, grafique la magnitud de X1_2/N2 en la subfigura superior, y la magnitud
% de X2_2/N2 en la subfigura inferior. Grafique ambas versus frecuencia, en el intervalo
% de 0 a 2*pi.
%datos
N2 = 2^nextpow2(N);
t2 = (0:(N2-1))*Ts;
%se�al
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
title(' se�al respecto frecuencia X2_1');
xlabel('frecuancia');
ylabel('se�al X1_1');
hold on;
subplot(2,1,2);
plot(wD,X2_2);
title(' se�al respecto frecuencia X2_2');
xlabel('frecuencia');
ylabel('se�al X2_2');

% �Qu� diferencias observa respecto a las gr�ficas de la figura 2?
%en las 2 se�ales se puede observar que los picos no se comoportan tanto
%como lineas verticales , mas bien como curvas por lo que estan mas
%suavizadas y tienen un poco mas de area lograda por la curvatura.


%% 4) Gr�ficas en intervalo de -pi a pi
% En la figura 4, grafique la magnitud de X1_2/N2 en la subfigura superior, y la magnitud
% de X2_2/N2 en la subfigura inferior, pero versus frecuencia en el intervalo de -pi a pi.
k = -N2/2:N2/2-1;
wf = (2*pi/N2)*k;

figure(4);clf;
subplot(2,1,1);
plot(wf,X2_1);
title(' se�al respecto frecuencia X2_1');
xlabel('frecuancia');
ylabel('se�al X2_1');
hold on;
subplot(2,1,2);
plot(wf,X2_2);
title('se�al respecto frecuencia X2_2');
xlabel('frecuencia');
ylabel('se�al X2_2');

% �Qu� puede decir respecto a la simetr�a del espectro de las se�ales?
% son casi la misma a excepcion del ruido del segundo grafico , su
% frecuencia sigue los mismo patrones, omo si la frecuencia fundamental
% fuera la misma.


%% 5) Aliasing
% Cree una se�al, x3, que sea la suma de dos sinusoides, igual que antes. Pero esta vez,
% el primer sinusoide debe tener una frecuencia f3 = 240 Hz, con amplitud A3 = A1 = 0.7.
% El segundo sinusoide debe tener una frecuencia f4 = 150 Hz, con amplitud A4 = A2 = 1 Hz.
% Use el mismo vector de tiempo usado para x1 y x2.
% Aplique la fft a x3, usando el n�mero N2 usado en la secci�n 3) (X3_2).
% En la figura 5, grafique la magnitud de X1_2/N2 en la subfigura superior, y la magnitud
% de X3_2/N2 en la subfigura inferior, versus frecuencia en el intervalo de -pi a pi.
%datos
Al3=0.7;
Al4=1;
f3=240;
f4=150;
%se�al
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
title(' se�al respecto frecuencia X2_1');
xlabel('frecuencia');
ylabel(' se�al X2_1(t)');
hold on;
subplot(2,1,2);
plot(f3,X3_1);
title('se�al respecto frecuencia X3_1');
xlabel('frecuencia');
ylabel(' se�al X3_1');

% �C�mo se comparan las gr�ficas anteriores? Explique sus observaciones.
%las se�ales son demasiado similares, no le encuentro diferencias.