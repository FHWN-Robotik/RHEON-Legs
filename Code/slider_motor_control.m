% Create the GUI
fig = uifigure('Name', 'Servo Motor Control');
fig.Position = [100 100 400 200];

% Create slider for Motor 1
slider1 = uislider(fig, 'Position', [100 130 200 3]);
slider1.Limits = [15 165];
slider1.Value = 90; % Initial position

% Create label for Motor 1
label1 = uilabel(fig, 'Position', [50 130 50 22], 'Text', 'Hip');

% Create slider for Motor 2
slider2 = uislider(fig, 'Position', [100 80 200 3]);
slider2.Limits = [90 165];
slider2.Value = 90; % Initial position

% Create label for Motor 2
label2 = uilabel(fig, 'Position', [50 80 50 22], 'Text', 'Knee');

% Initialize serial connection to Arduino
device = serialport('COM7', 9600);

% Callback for Slider 1
slider1.ValueChangedFcn = @(src, event) updateAngles(device, slider1.Value, slider2.Value);

% Callback for Slider 2
slider2.ValueChangedFcn = @(src, event) updateAngles(device, slider1.Value, slider2.Value);

% Function to send both angles to Arduino
function updateAngles(device, angle1, angle2)
    % Convert angles to int16 and send them as two consecutive 16-bit values
    write(device, [int16(angle1) int16(angle2)], "int16");
end
