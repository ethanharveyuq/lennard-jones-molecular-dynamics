import matplotlib.animation as animation
import matplotlib.pyplot as plt
import pandas as pd

# Load file
df = pd.read_csv("output.csv")
print(df.head())
print(df.shape)
print(df["x"].min(), df["x"].max(), df["y"].min(), df["y"].max())

# Set up the plot
fig, ax = plt.subplots(figsize=(10, 10))
(scat,) = ax.plot([], [], "bo", ms=5)

# plot limits
ax.set_xlim(0, 10)
ax.set_ylim(0, 10)

# Get unique time steps/frames
frames = sorted(df["step"].unique())


# Animation update function
def update(frame_idx):
  current_data = df[df["step"] == frames[frame_idx]]
  scat.set_data(current_data["x"], current_data["y"])
  return (scat,)


# Create animation
ani = animation.FuncAnimation(fig, update, frames=len(frames), interval=1000)

plt.xlabel("X Position")
plt.ylabel("Y Position")
plt.title("Particle Movement Simulation")
plt.show()