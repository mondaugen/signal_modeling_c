% Visualizes the evolution of the filter coefficients in one figure and the
% error signal in the other.
% In the parent script (e.g., the prompt) define the variables:
% filepath - relative path to data file
% p        - the order of the adaptive filter
f=fopen(filepath,'r');
data=fread(f,Inf,'double');
data=data(:)';
data=reshape(data,p+1,length(data)/(p+1))';
A=data(:,1:(end-1));
e=data(:,end);
figure(1);
plot((1:length(e)),A);
figure(2);
plot(1:length(e),e);
