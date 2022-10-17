import asyncio
import queue


received_queue = queue.Queue()


async def wait_for_data(queue: queue.Queue, timeout: float):
    waited_time = 0
    while queue.empty():
        await asyncio.sleep(0.1)
        waited_time += 0.1
        if waited_time > timeout:
            return "timeout"
    return queue.get_nowait()


def clear_queue():
    while not received_queue.empty():
        received_queue.get()
        received_queue.task_done()


async def get_data(timeout: float = 5) -> str:
    data = await wait_for_data(received_queue, timeout)
    return data


def put_data(data):
    received_queue.put_nowait(data)
