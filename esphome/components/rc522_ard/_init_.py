import asyncio
import logging
from esphome.components.sensor import SensorEntity
from esphome.const import CONF_NAME, CONF_PORT, CONF_BAUDRATE
from esphome.core import HomeAssistant
from esphome.config_entries import ConfigEntry
from esphome.helpers.entity_platform import AddEntitiesCallback

_LOGGER = logging.getLogger(__name__)

async def async_setup_entry(
    hass: HomeAssistant, entry: ConfigEntry, add_entities: AddEntitiesCallback
) -> None:
    port = entry.data[CONF_PORT]
    baudrate = entry.data[CONF_BAUDRATE]
    name = entry.data[CONF_NAME]

    reader, writer = await asyncio.open_serial_connection(url=port, baudrate=baudrate)

    add_entities([ESP32UARTSensor(reader, writer, name)])

class ESP32UARTSensor(SensorEntity):
    def __init__(self, reader, writer, name):
        self._reader = reader
        self._writer = writer
        self._name = name
        self._state = None

    @property
    def name(self):
        return self._name

    @property
    def state(self):
        return self._state

    async def async_update(self):
        try:
            data = await self._reader.read(100)
            if data:
                self._state = data.decode().strip()
        except Exception as e:
            _LOGGER.error(f"Error reading from serial port: {e}")

    async def async_will_remove_from_hass(self):
        self._writer.close()
        await self._writer.wait_closed()
