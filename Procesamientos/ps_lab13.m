%% Laboratorio 13
% Alejandro Windevoxhel  16047
% Lectura de audio
[x, Fs] = audioread('guitarloop.wav');
soundsc(x,Fs);
% Vector Tiempo
N1 = length(x);
Ts = 1/Fs;
t1 = (0:(N1-1))*Ts;
% Para limpiar el audio es necesario implementar un filtro notch que nos
% permita eliminar las frecuencias de ruido sin intervenir con las
% frecuencias cercanas. 
%% Diseno del filtro Notch en 2KHz
f0 = 2000;
r = 0.999;
w0 = (2*pi*f0)/Fs;
b1 = [1, -2*cos(w0),1];
a1 = [1, -2*r*cos(w0),r^2];
H1 = tf(b1,a1,Ts);
%% Diseno del filtro Notch en 500Hz
f02 = 500;
r2 = 0.999;
w02 = (2*pi*f02)/Fs;
b2 = [1, -2*cos(w02),1];
a2 = [1, -2*r2*cos(w02),r2^2];
H2 = tf(b2,a2,Ts);
%% Filtro a Implementar
H3 = H2*H1;
NH = H3.Numerator{1};
DH = H3.Denominator{1};
[h,w] = freqz(NH,DH,2^16);
f = w*Fs/(2*pi);
%% Generacion de Senal Combinada
t = ((0:(Fs-1))*Ts);
f1 = 450;
f2 = 500;
f3 = 550;
f4 = 1950;
f5 = 2000;
f6 = 2050;
S = sin(2*pi*f1*t)+sin(2*pi*f2*t)+sin(2*pi*f3*t)+sin(2*pi*f4*t)+sin(2*pi*f5*t)+sin(2*pi*f6*t);
SF = filter(NH,DH,S);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Espectros de Amplitud Unilateral
% Entrada
N = 44100;
XC2 = fft(S,N);
P2 = abs(XC2/N);
PCX12 = P2(1,1:N/2+1);
PCX12(1,2:end-1) = 2*PCX12(1,2:end-1);
% Salida
YC1 = fft(SF,N);
PY2 = abs(YC1/N);
PY1 = PY2(1,1:N/2+1);
PY1(1,2:end-1) = 2*PY1(1,2:end-1);
%Vecotr de frecuencias en HZ
VF = Fs*(0:(N/2))/N;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Graficas
figure(1) 
clf;
subplot(2,1,1)
stem(VF,PCX12) 
xlim([0 2501])
title('Espectro Unilateral X1')
xlabel('frecuencia (Hz)')
ylabel('|X1(f)|')
subplot(2,1,2)
stem(VF,PY1) 
xlim([0 2501])
title('Espectro Unilateral X2')
xlabel('frecuencia (Hz)')
ylabel('|Y2(f)|')
ylim([0,1.5]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Filtrado del Audio de Guitarra
y = filter(NH,DH,x);
%soundsc(y,Fs);
% Separacion de Canales
C1_X = x(:,1)';
C2_X = x(:,2)';
C1_Y = x(:,1)';
C2_Y = x(:,2)';
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Espectros de Amplitud Unilateral
% Entrada Canal 1
NC = size(x,1);
XC1 = fft(C1_X,NC);
PXC2 = abs(XC1/NC);
PXC1 = PXC2(1,1:NC/2+1);
PXC1(1,2:end-1) = 2*PXC1(1,2:end-1);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Entrada Canal 2
NC = 332214;
XC2 = fft(C2_X,NC);
PXC22 = abs(XC2/NC);
PXC12 = PXC22(1,1:NC/2+1);
PXC12(1,2:end-1) = 2*PXC12(1,2:end-1);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Salida Canal 1
YC1 = fft(C1_Y,NC);
PYC2 = abs(YC1/NC);
PYC1 = PYC2(1,1:NC/2+1);
PYC1(1,2:end-1) = 2*PYC1(1,2:end-1);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Salida Canal 2
YC2 = fft(C2_Y,NC);
PYC22 = abs(YC2/NC);
PYC12 = PYC22(1,1:NC/2+1);
PYC12(1,2:end-1) = 2*PYC12(1,2:end-1);
%Vecotr de frecuencias en HZ
VFC = Fs*(0:(NC/2))/NC;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Graficas
figure(2) 
clf;
subplot(2,2,1)
plot(VFC,PXC1) 
title('Espectro Canal 1 Entrada')
xlabel('frecuencia (Hz)')
ylabel('|X1(f)|')
xlim([0,4000]);
ylim([0,0.13]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,2)
plot(VFC,PXC12) 
title('Espectro Canal 2 Entrada')
xlabel('frecuencia (Hz)')
ylabel('|X1(f)|')
xlim([0,4000]);
ylim([0,0.13]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,3)
plot(VFC,PYC1) 
title('Espectro Canal 1 Salida')
xlabel('frecuencia (Hz)')
ylabel('|Y1(f)|')
xlim([0,4000]);
ylim([0,0.13]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(2,2,4)
plot(VFC,PYC12) 
title('Espectro Canal 2 Salida')
xlabel('frecuencia (Hz)')
ylabel('|Y1(f)|')
xlim([0,4000]);
ylim([0,0.13]);





