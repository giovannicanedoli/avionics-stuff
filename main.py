import csv
import matplotlib.pyplot as plt
import numpy as np

# Function to clean up the data and test stateTick for each data point
def clenup(namefile):
    # Read data from CSV
    with open(namefile) as f:
        reader = csv.reader(f)
        data = list(reader)

    # Convert data to numerical format (assuming data is in string format)
    data = [[float(x), float(y)] for x, y in data]

    # Initialize variables
    len_data = len(data)
    data2 = []
    results = []  # List to store the results

    # Apply pressure difference condition and filter data
    for i in range(1, len_data):
        # Check for difference of exactly ±7000 Pascal
        if data[i][1] - data[i-1][1] not in range(-7000, 7000):
            data[i][1] = data[i-1][1]

        # Append filtered x and y values
        data2.append([data[i][0], data[i][1]])

    # Call stateTick for each data point and accumulate results
    for i in range(len(data)):
        delta = data[i][0]
        pressure = data[i][1]
        result = stateTick(delta, pressure)
        results.append(result)

    # Print all the results at once
    print(results)

    # Separate the filtered data into x and y for plotting
    x_vals = [row[0] for row in data2]
    y_vals = [row[1] for row in data2]

    # Plot the filtered data
    plt.figure(figsize=(10, 6))

    # Plot the data with different background colors for each state
    plot_with_intervals(x_vals, y_vals)

    plt.xlabel('Delta (X values)')
    plt.ylabel('Pressure (Y values)')
    plt.title('Pressure Plot with State-Specific Coloring')
    plt.grid(True)
    plt.show()

# Function to determine the state based on delta and pressure
def stateTick(delta, pressure):
    if 5197 <= delta < 24000:
        return "su rampa"
    elif 24000 <= delta < 26000:
        return "lancio"
    elif 26000 <= delta < 27000:
        return "apogeo"
    elif 37000 <= delta < 706009:
        return "a terra"
    else:
        return 'altro'

# Function to plot the intervals with different colors
def plot_with_intervals(x_vals, y_vals):
    plt.plot(x_vals, y_vals, color='black')  # Plot the data line

    # Define intervals with corresponding colors
    intervals = [
        (5197, 24000, 'lightblue', 'su rampa'),
        (24000, 26000, 'green', 'lancio'),
        (26000, 27000, 'yellow', 'apogeo'),
        (37000, 706009, 'red', 'a terra')
    ]

    x_vals = np.array(x_vals)  # Convert to NumPy array for easier boolean operations

    # Fill background colors for each interval
    for start, end, color, label in intervals:
        mask = (x_vals >= start) & (x_vals < end)  # Create boolean mask
        plt.fill_between(x_vals, y_vals, where=mask, color=color, alpha=0.3, label=label)

    plt.legend()

# Main function to run the cleanup process and testing
if __name__ == '__main__':
    # Call cleanup function with actual CSV data
    clenup('data.csv')
