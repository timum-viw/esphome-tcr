import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor, i2c

CODEOWNERS = ["@timum-viw"]
DEPENDENCIES = ["i2c"]
ICON_QRCODE = "mdi:qrcode"

tcr_ns = cg.esphome_ns.namespace("tcr")
TcrSensor = tcr_ns.class_(
    "TcrSensor", text_sensor.TextSensor, cg.Component, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema(
        TcrSensor,
        icon=ICON_QRCODE,
    )
    .extend(cv.polling_component_schema("500ms"))
    .extend(i2c.i2c_device_schema(0x0c))
)


async def to_code(config):
    var = await text_sensor.new_text_sensor(config)
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)