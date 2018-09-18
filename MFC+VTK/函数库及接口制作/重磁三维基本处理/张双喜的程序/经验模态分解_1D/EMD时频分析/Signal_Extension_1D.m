
function [Data_extension,k1,k2]=Signal_Extension_1D(Data,signal_length,K)
% data ��ʾԭʼ�źţ�K ��ʾ���ߺ��źŵĳ���
% Data_extension ��ʾ���ص������ź�
% k1,k2 �ֱ��ʾ���ص��ź��������ߵĵ���

Length=K-signal_length; % ��Ҫ���غ��źų���
Data_extension=zeros(1,K);
if mod(Length,2)==0    % ��Ϊż�������ҷ���ĵ������
    k1=Length/2;
    k2=k1;
      for i=1:K
          if i<=(Length/2)
             Data_extension(i)=Data(Length/2-i+2);
          elseif (i>(Length/2) && i<=(signal_length+Length/2))
             Data_extension(i)=Data(i-Length/2);
          elseif (i>(signal_length+Length/2))
             Data_extension(i)=Data(signal_length-(i-(signal_length+Length/2)));
          end
      end 
else  % ��Ϊ�����������ֵ���Ҳ���ֵС  
    k1=(Length+1)/2;
    k2=(Length-1)/2;
      for i=1:K
          if i<=((Length+1)/2)
             Data_extension(i)=Data((Length+1)/2-i+2);
          elseif (i>((Length+1)/2) && i<=(signal_length+(Length+1)/2))
             Data_extension(i)=Data(i-(Length+1)/2);
          elseif (i>(signal_length+(Length+1)/2))
             Data_extension(i)=Data(signal_length-(i-(signal_length+(Length+1)/2)));
          end
      end         
end