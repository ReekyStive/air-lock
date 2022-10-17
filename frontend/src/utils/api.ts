const addr = "http://127.0.0.1:5001";


export async function status() {
  const resp = await fetch(`${addr}/status`);
  return await resp.json();
}


export async function open(password: string) {
  const params = new URLSearchParams({ password: password });
  const url = `${addr}/open?${params.toString()}`;
  const resp = await fetch(url, { method: 'get' });
  const data = await resp.json();
  return data;
}

export async function playMelody(password: string, melodyId: number) {
  const params = new URLSearchParams({ password: password, id: melodyId.toString() });
  const url = `${addr}/play-melody?${params.toString()}`;
  const resp = await fetch(url, { method: 'get' });
  const data = await resp.json();
  return data;
}

export async function setAngle(password: string, angle: number) {
  const params = new URLSearchParams({ password: password, angle: angle.toString() });
  const url = `${addr}/set-angle?${params.toString()}`;
  const resp = await fetch(url, { method: 'get' });
  const data = await resp.json();
  return data;
}

export async function changePassword(currentPassword: string, newPassword: string) {
  const params = new URLSearchParams({ password: currentPassword, new: newPassword });
  const url = `${addr}/change-password?${params.toString()}`;
  const resp = await fetch(url, { method: 'get' });
  const data = await resp.json();
  return data;
}
