
function [Data_cut]=Signal_Cut_1D(Data_extension,k1,k2)
% Data_extension ��ʾ���ߺ�����ݣ� k1,k2��ʾ�����ߵĵ���
% Data_cut ��ʾ����������

Length=length(Data_extension); 
NUM=Length-k1-k2; % ���ߺ��źų���
Data_cut=zeros(1,NUM);
for i=1:Length
    if(i>=k1+1 && i<=Length-k2)
       Data_cut(i-k1)=Data_extension(i);
    end
end





