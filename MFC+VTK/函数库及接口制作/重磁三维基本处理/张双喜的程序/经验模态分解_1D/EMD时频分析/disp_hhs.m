%DISP_HHS  display Hilbert-Huang spectrum
%
% DISP_HHS(im,t,inf)
% displays in a new figure the spectrum contained in matrix "im"
% (amplitudes in dB).
%
% inputs:  - im: image matrix (e.g., output of "toimage")
%          - t (optional): time instants (e.g., output of "toimage") 
%          - inf (optional): -dynamic range in dB (wrt max)
%            default: inf = -20
%          - fs: sampling frequency
%
% use:  disp_hhs(im) ; disp_hhs(im,t) ; disp_hhs(im,inf)
%       disp_hhs(im,t,inf) ; disp_hhs(im,inf,fs) ; disp_hhs(im,[],fs)
%       disp_hhs(im,t,[],fs) ; disp_hhs(im,t,inf,fs)
%
%
% See also
%  emd, hhspectrum, toimage
%
% G. Rilling, last modification 3.2007
% gabriel.rilling@ens-lyon.fr

function [t,im]=disp_hhs(varargin)

error(nargchk(2,3,nargin));
fs = 0;
inf = -20;
im = varargin{1};
t = 1:size(im,2);
switch nargin
  case 1
    %raf
  case 2
    if isscalar(varargin{2})
      inf = varargin{2};
    else
      t = varargin{2};
    end
  case 3
    if isvector(varargin{2})
      t = varargin{2};
      inf = varargin{3};
    else
      inf = varargin{2};
      fs = varargin{3};
    end
  case 4
    t = varargin{2};
    inf = varargin{3};
    fs = varargin{4};
end

if isempty(inf)
  inf = -20;
end

if inf > 0
  inf = -inf;
elseif inf == 0
  error('inf must be nonzero')
end

M=max(max(im));

warning off
im = 10*log10(im/M);
warning on

figure

if fs == 0
  imagesc(t,[0,0.5],im,[inf,0]);
  %ylabel('normalized frequency');
  ylabel('Ƶ�� /Hz','FontName','Times New Roman');
else
  imagesc(t,[0,0.5*fs],im,[inf,0]);
  %ylabel('frequency  f/Hz');
  ylabel('Ƶ�� /Hz','FontName','Times New Roman');
end
set(gca,'YDir','normal');
xlabel('ʱ�� /s','FontName','Times New Roman');
%xlabel('time  t/ms');
%title('Hilbert-Huang spectrum')
%text(1900,950,'(a)','FontSize',14,'FontName','Times New Roman');% ��ͼ�����Ͻ���ʾ��(a)��
