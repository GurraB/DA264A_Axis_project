function PlotValuesFromArduino(comPort)

delete(instrfindall);   %close all com ports used by MATLAB
arduino = setupSerial(comPort); %setup communication

    %initialize
    if(~exist('myAxes','var'))
        buf_len = 1000; %amount of values on x-axis
        index = 1:buf_len;
        zeroIndex = zeros(size(index)); 
        
        tcdata = zeroIndex; %fill X data with zeros
        tcdata1 = zeroIndex;
        tcdata2 = zeroIndex;
        
        limits_bottom = -32768; %bottom value of the plot
        limits_top = 32768;     %top value of the plot
        limits = [limits_bottom limits_top];    %push it to the limit
    
        axes('Xlim',[0 buf_len],'Ylim',limits); %create axes
        grid on;    %enable grid
    
        l = line(index,[tcdata;zeroIndex]);     %X line
        l1 = line(index,[tcdata1;zeroIndex]);   %Y line
        l2 = line(index,[tcdata2;zeroIndex]);   %Z line
        drawnow;    %draw it!
    end

    while (1)
        tc = readValue(arduino);    %read the value from the arduino
        disp(tc);
        if (isnumeric(tc))  %we don't want to plot something that's not a number
            tcdata = [tcdata(2:end),tc(1)];     %append the new X value
            tcdata1 = [tcdata1(2:end),tc(2)];
            tcdata2 = [tcdata2(2:end),tc(3)];
            set(l,'Ydata',tcdata);              %set the Y data to be 'l'
            set(l1,'Ydata',tcdata1, 'Color', 'blue');
            set(l2,'Ydata',tcdata2, 'Color', 'red');
            drawnow;    %draw it!
        end
    end
end

function [output] = readValue(s)
output = fscanf(s,'%f');    %read on com port
end


function[obj] = setupSerial(comPort)
obj = serial(comPort);  %set obj to be a com port
set(obj,'DataBits',8);  %set the data to be transfered in 8 bits at the time
set(obj,'StopBits',1);  %I don't know
set(obj,'BaudRate',115200); %baudrate, same as on Arduino!
set(obj,'Parity','none');   %no parity bit
fopen(obj); %open the com port
mbox = msgbox('Serial Communication setup'); uiwait(mbox);  %show message that the port is setup
fscanf(obj,'%u');   %read on port
end