
%%lab 13 
%seccion 10

%Juan Gerardo Gonzalez MOrales 
%carne:17594
%parte 1 :audio
[x, Fs] = audioread('guitarloop.wav');
soundsc(x,Fs);

Ts = 1/Fs;
N1 = length(x);

t1 = (0:(N1-1))*Ts;

%Para poder tener un audio mas limpio se necesita usar un filtro tipo notch
%ya que podemos hacer un audio mas limpio o sin ruido sin molestar a la frecuencia.


%%
%firo notch 2k Hz

r = 0.999;
fa = 2000;
wa = (2*pi*fa)/Fs;
au1 = [1, -2*r*cos(wa),r^2];
bu1 = [1, -2*cos(wa),1];

HF = tf(bu1,au1,Ts)
%firo notch 500 Hz

r2 = 0.999;
fb = 500;
wa2 = (2*pi*fb)/Fs;
au2 = [1, -2*r2*cos(wa2),r2^2];
bu2 = [1, -2*cos(wa2),1];


HF2 = tf(bu2,au2,Ts)

%filtro notch Hf1 * Hf2
HF3 = HF2*HF
Na = HF3.Numerator{1};
Da = HF3.Denominator{1};
Hlow = dfilt.df1(bu1,au1);
Hhigh = dfilt.df1(bu2,au2);
hcas = dfilt.cascade(Hlow,Hhigh);
fvtool(hcas,'Fs',Fs);

[h,w] = freqz(Na,Da,2^16);

f = w*Fs/(2*pi);
%% 
%señal de diferentes frecuencias

f1 = 450;
f2 = 500;
f3 = 550;
f4 = 1950;
f5 = 2000;
f6 = 2050;
t = ((0:(Fs-1))*Ts);
SN = sin(2*pi*f1*t)+sin(2*pi*f2*t)+sin(2*pi*f3*t)+sin(2*pi*f4*t)+sin(2*pi*f5*t)+sin(2*pi*f6*t);
Fl = filter(Na,Da,SN);
%%
% señales unilaterales

%canales entrada
N = 44100;
Xf2 = fft(SN,N);
P2 = abs(Xf2/N);
P3 = P2(1,1:N/2+1);
P3(1,2:end-1) = 2*P3(1,2:end-1);
%cnal salida
Yf1 = fft(Fl,N);
P4 = abs(Yf1/N);
P5 = P4(1,1:N/2+1);
P5(1,2:end-1) = 2*P5(1,2:end-1);

Vy = Fs*(0:(N/2))/N;

figure(1);clf; 

subplot(2,1,1)
stem(Vy,P3) 
xlim([0 2501])
title('señal x1')
xlabel('frecuencia en Hz ')
ylabel('x1(f)')
subplot(2,1,2)
stem(Vy,P5) 
xlim([0 2501])
title('señal x2')
xlabel('frecuencia en Hz')
ylabel('y2(f)|')
ylim([0,1.5]);

%% 
%limpieza audio
yf = filter(Na,Da,x);
%soundsc(yf,Fs);
% canales
CX1 = x(:,1)';
CX2 = x(:,2)';
CY1 = yf(:,1)';
CY2 = yf(:,2)';

% señales de audio 
% Channel 1
N1c = size(x,1);
X1C = fft(CX1,N1c);
P6 = abs(X1C/N1c);
P7 = P6(1,1:N1c/2+1);
P7(1,2:end-1) = 2*P7(1,2:end-1);
% Entrada Canal 2
N1c = 332214;
Xf2 = fft(CX2,N1c);
P8 = abs(Xf2/N1c);
P9 = P8(1,1:N1c/2+1);
P9(1,2:end-1) = 2*P9(1,2:end-1);

% Salida Canal 1
Yf1 = fft(CY1,N1c);
p10 = abs(Yf1/N1c);
p11 = p10(1,1:N1c/2+1);
p11(1,2:end-1) = 2*p11(1,2:end-1);

% Salida Canal 2
Yf2 = fft(CY2,N1c);
P12 = abs(Yf2/N1c);
P13 = P12(1,1:N1c/2+1);
P13(1,2:end-1) = 2*P13(1,2:end-1);
%Vecotr de frecuencias en HZ
VFC = Fs*(0:(N1c/2))/N1c;



% Graficas
figure(2); clf;
subplot(2,2,1)
plot(VFC,P7) 
title('CH 1  entrada')
xlabel('frecuencia en hz')
ylabel('x1(f)')
xlim([0,4000]);
ylim([0,0.13]);
subplot(2,2,2)
plot(VFC,P9) 
title('CH 2  entrada')
xlabel('frecuencia en hz')
ylabel('x1(f)')
xlim([0,4000]);
ylim([0,0.13]);
subplot(2,2,3)
plot(VFC,p11) 
%%
title('CH 1  salida')
xlabel('frecuencia en hz')
ylabel('|Y1(f)|')
xlim([0,4000]);
ylim([0,0.13]);

subplot(2,2,4)
plot(VFC,P13) 
title('CH 2  salida')
xlabel('frecuencia en hz')
ylabel('y1(f)')
xlim([0,4000]);
ylim([0,0.13]);


%% audio grabado
audiowrite('señal_pura.wav',yf,Fs);


