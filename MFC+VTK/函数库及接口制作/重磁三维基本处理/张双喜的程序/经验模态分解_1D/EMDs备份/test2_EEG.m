
%spo2_0p6.txt;%ecg1410.txt;%spo2_3p.txt;%spo2_0p2.txt ;% spo2_3p.txt;spo2_0p4.txt spo2_3p.txt
%result = spo2_0p2;%pecg1410.txt;
% len=500;
% x = [1:len];
clear
clc
close all

load eeg0410.txt;
rdxn=eeg0410;
% load eeg0410.mat;
% rdxn=eeg0410;
N=512;
n=0:N-1;
fs=100;
X=fft(rdxn,N);
figure;
plot(n*fs/N,abs(X));

%�ڶ����������ֽ��Ǻ������������
%rdxn = result([(x-1)*5+4])*256 +result([(x-1)*5+5]);

figure;
plot(rdxn);
title('�Ե�ͼ��EEG');

[imf,ort,nbits]=emd(rdxn);
imfsize=size(imf);
i=imfsize(1);

%��IMF����
figure;
for j=1:i
    subplot(i/2+1,2,j);plot(imf(j,:));
end
%title('EMD�ֽ�');
%ÿ�ֽ�һ�κ�Ĳ�����
% figure;
% newrdxn=rdxn;
% for k=1:i
%     newrdxn=newrdxn-imf(k,:);
%     subplot(i/2+1,2,k);plot(newrdxn);
% end
% title('������');


%HHT�任
[A,f,tt] = hhspectrum(imf(1:end-1,:));
[im,tt,ff] = toimage(A,f,tt,512);
disp_hhs(im,tt);
hgsave('HH_Spectrum');
%HHT�߼���
for kkk=1:512
    aaa(kkk)=sum(im(kkk,:));
end
figure;
plot(ff(1,:),aaa);
%plot(aaa);
% figure;

%plot(n*100/N,aaa);